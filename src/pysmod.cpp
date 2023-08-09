#include "pysmod.h"


//--------------------------------------------------------------------//
// CPyPluginInfo                                                      //
//--------------------------------------------------------------------//
CPyPluginInfo::CPyPluginInfo(PyObject *pModule, const char *pModuleName)
{
    this->m_pModule = pModule;
    Py_INCREF(this->m_pModule);
    strncpy(this->m_sModuleName, pModuleName, sizeof(this->m_sModuleName) - 1);

    this->ClearInfo();
    if (!this->Read())
    {
        LogPythonErrorIfAny();
        this->m_bIsValid = false;
        return;
    }

    this->m_bIsValid = true;
}

CPyPluginInfo::~CPyPluginInfo()
{
    Py_XDECREF(this->m_pModule);
}

const char *CPyPluginInfo::GetName()
{
    return this->m_sName;
}

const char *CPyPluginInfo::GetDescription()
{
    return this->m_sDescription;
}

const char *CPyPluginInfo::GetAuthor()
{
    return this->m_sAuthor;
}

const char *CPyPluginInfo::GetVersion()
{
    return this->m_sVersion;
}

const char *CPyPluginInfo::GetUrl()
{
    return this->m_sUrl;
}

bool CPyPluginInfo::IsValid()
{
    return this->m_bIsValid;
}

void CPyPluginInfo::ClearInfo()
{
    memset(this->m_sName, '\0', sizeof(this->m_sName));
    memset(this->m_sDescription, '\0', sizeof(this->m_sDescription));
    memset(this->m_sAuthor, '\0', sizeof(this->m_sAuthor));
    memset(this->m_sVersion, '\0', sizeof(this->m_sVersion));
    memset(this->m_sUrl, '\0', sizeof(this->m_sUrl));
}

bool CPyPluginInfo::Read()
{
    PyObject *pDict = NULL;
    PyObject *pKey = NULL;
    PyObject *pValue = NULL;

    const char *keys[] = {
        "name",
        "description",
        "author",
        "version",
        "url"
    };

    pDict = PyObject_GetAttrString(this->m_pModule, "PLUGIN_INFO");
    if (pDict == NULL)
    {
        g_pSM->LogError(myself, "Could not find PLUGIN_INFO in '%s' module.", this->m_sModuleName);
        PyErr_Restore(NULL, NULL, NULL);  // Suppress error
        return false;
    }

    if (PyDict_Size(pDict) != PLUGIN_INFO_SIZE)
    {
        Py_DECREF(pDict);
        g_pSM->LogError(myself, "Object PLUGIN_INFO in '%s' module is incomplete.", this->m_sModuleName);
        return false;
    }

    for (int i = 0; i < sizeof(keys) / sizeof(const char*); i++)
    {
        pKey = PyUnicode_FromString(keys[i]);
        pValue = PyDict_GetItemWithError(pDict, pKey);
        if (pValue == NULL)
        {
            LogPythonErrorIfAny();
            Py_DECREF(pKey);
            Py_DECREF(pDict);
            g_pSM->LogError(
                myself,
                "Could not retrieve PLUGIN_INFO['%s'] from '%s' module.",
                keys[i],
                this->m_sModuleName
            );
            return false;
        }
        Py_INCREF(pValue);

        if (strcmp(keys[i], "name") == 0)
            strncpy(this->m_sName, PyUnicode_AsUTF8(pValue), sizeof(this->m_sName) - 1);
        else if (strcmp(keys[i], "description") == 0)
            strncpy(this->m_sDescription, PyUnicode_AsUTF8(pValue), sizeof(this->m_sDescription) - 1);
        else if (strcmp(keys[i], "author") == 0)
            strncpy(this->m_sAuthor, PyUnicode_AsUTF8(pValue), sizeof(this->m_sAuthor) - 1);
        else if (strcmp(keys[i], "version") == 0)
            strncpy(this->m_sVersion, PyUnicode_AsUTF8(pValue), sizeof(this->m_sVersion) - 1);
        else if (strcmp(keys[i], "url") == 0)
            strncpy(this->m_sUrl, PyUnicode_AsUTF8(pValue), sizeof(this->m_sUrl) - 1);

        Py_DECREF(pValue);
        Py_DECREF(pKey);
    }

    Py_DECREF(pDict);
    return true;  // Success
}


//--------------------------------------------------------------------//
// CPyPlugin                                                          //
//--------------------------------------------------------------------//
CPyPlugin::CPyPlugin(PyObject *pModule, const char *pModuleName, const char *pAbsolutePath, const char *pRelativePath)
{
    this->m_pModule = pModule;

    memset(this->m_sModuleName, '\0', sizeof(this->m_sModuleName));
    memset(this->m_sAbsolutePath, '\0', sizeof(this->m_sAbsolutePath));
    memset(this->m_sRelativePath, '\0', sizeof(this->m_sRelativePath));

    strncpy(this->m_sModuleName, pModuleName, sizeof(this->m_sModuleName) - 1);
    strncpy(this->m_sAbsolutePath, pAbsolutePath, sizeof(this->m_sAbsolutePath) - 1);
    strncpy(this->m_sRelativePath, pRelativePath, sizeof(this->m_sRelativePath) - 1);

    this->m_pPluginInfo = new CPyPluginInfo(pModule, pModuleName);
}

CPyPlugin::~CPyPlugin()
{
    delete this->m_pPluginInfo;
    this->m_pPluginInfo = NULL;

    Py_DECREF(m_pModule);
}

PyObject *CPyPlugin::GetModule()
{
    return this->m_pModule;
}

const char *CPyPlugin::GetModuleName()
{
    return this->m_sModuleName;
}

const char *CPyPlugin::GetAbsolutePath()
{
    return this->m_sAbsolutePath;
}

const char *CPyPlugin::GetRelativePath()
{
    return this->m_sRelativePath;
}

CPyPluginInfo *CPyPlugin::GetInfo()
{
    return this->m_pPluginInfo;
}

bool CPyPlugin::IsValid(PyObject *pModule)
{
    PyObject* pInfo = PyObject_GetAttrString(pModule, "PYSMOD_PLUGIN");
    if (pInfo == NULL)
    {
        return false;
    }
    Py_DECREF(pInfo);
    return true;
}


//--------------------------------------------------------------------//
// CPyPluginManager                                                   //
//--------------------------------------------------------------------//
CPyPluginManager::CPyPluginManager()
{
    char pysmod_path[PLATFORM_MAX_PATH];
    memset(pysmod_path, '\0', sizeof(pysmod_path));
    GetPySModPath(pysmod_path, sizeof(pysmod_path) - 1);
    this->AddToPythonPath(pysmod_path);
    this->LoadPluginsFromDir(pysmod_path, NULL);
    this->Call_OnPluginStart();
}

CPyPluginManager::~CPyPluginManager()
{
    this->Call_OnPluginEnd();
    this->UnloadAll();

    Py_XDECREF(this->m_pSysModule);
    Py_XDECREF(this->m_pPathList);
}

void CPyPluginManager::AddToPythonPath(const char *pszPath)
{
    if (this->m_pSysModule == NULL && this->m_pPathList == NULL)
    {
        this->m_pSysModule = PyImport_ImportModule("sys");
        this->m_pPathList = PyObject_GetAttrString(this->m_pSysModule, "path");
    }

    PyList_Append(this->m_pPathList, PyUnicode_FromString(pszPath));
}

void CPyPluginManager::LoadPluginsFromDir(const char *pszBaseDir, const char *pszLocalPath)
{
    char szBasePath[PLATFORM_MAX_PATH];
    memset(szBasePath, '\0', sizeof(szBasePath));

    if (pszLocalPath == NULL)
    {
        libsys->PathFormat(szBasePath, sizeof(szBasePath), "%s", pszBaseDir);
    }
    else
    {
        libsys->PathFormat(szBasePath, sizeof(szBasePath), "%s/%s", pszBaseDir, pszLocalPath);
    }

    IDirectory *pDirectory = libsys->OpenDirectory(szBasePath);

    if (!pDirectory)
    {
        char szError[256];
        memset(szError, '\0', sizeof(szError));
        libsys->GetPlatformError(szError, sizeof(szError));
        g_pSM->LogError(myself, "Failure reading from plugins path: %s", pszLocalPath);
        g_pSM->LogError(myself, "Platform returned error: %s", szError);
        return;
    }

    while (pDirectory->MoreFiles())
    {
        if (pDirectory->IsEntryDirectory()
            && (strcmp(pDirectory->GetEntryName(), ".") != 0)
            && (strcmp(pDirectory->GetEntryName(), "..") != 0)
            && (strcmp(pDirectory->GetEntryName(), "disabled") != 0)
            && (strcmp(pDirectory->GetEntryName(), "optional") != 0)
            && (strcmp(pDirectory->GetEntryName(), "__pycache__") != 0))
        {
            char szNewLocal[PLATFORM_MAX_PATH];
            memset(szNewLocal, '\0', sizeof(szNewLocal));
            if (pszLocalPath == NULL)
            {
                strncpy(szNewLocal, pDirectory->GetEntryName(), sizeof(szNewLocal) - 1);
            }
            else
            {
                libsys->PathFormat(szNewLocal, sizeof(szNewLocal), "%s/%s", pszLocalPath, pDirectory->GetEntryName());
            }

            char szAbsolutePath[PLATFORM_MAX_PATH];
            memset(szAbsolutePath, '\0', sizeof(szAbsolutePath));
            libsys->PathFormat(szAbsolutePath, sizeof(szAbsolutePath), "%s/%s", pszBaseDir, szNewLocal);
            this->AddToPythonPath(szAbsolutePath);  // Python search path

            LoadPluginsFromDir(pszBaseDir, szNewLocal);
        }
        else if (pDirectory->IsEntryFile())
        {
            const char *pszFilename = pDirectory->GetEntryName();
            size_t len = strlen(pszFilename);
            if (len >= 4 && strcmp(&pszFilename[len - 3], ".py") == 0)
            {
                char szRelativePath[PLATFORM_MAX_PATH];
                memset(szRelativePath, '\0', sizeof(szRelativePath));
                if (pszLocalPath == NULL)
                {
                    strncpy(szRelativePath, pszFilename, sizeof(szRelativePath) - 1);
                }
                else
                {
                    libsys->PathFormat(szRelativePath, sizeof(szRelativePath), "%s/%s", pszLocalPath, pszFilename);
                }

                char szAbsolutePath[PLATFORM_MAX_PATH];
                memset(szAbsolutePath, '\0', sizeof(szAbsolutePath));
                libsys->PathFormat(szAbsolutePath, sizeof(szAbsolutePath), "%s/%s", pszBaseDir, szRelativePath);
                this->LoadPlugin(szAbsolutePath, szRelativePath);
            }
        }
        pDirectory->NextEntry();
    }
    libsys->CloseDirectory(pDirectory);
}

void CPyPluginManager::LoadPlugin(const char *szAbsolutePath, const char *szRelativePath)
{
    // Filename + extension.
    char szFilename[PLATFORM_MAX_PATH];
    memset(szFilename, '\0', sizeof(szFilename));
    libsys->GetFileFromPath(szFilename, sizeof(szFilename), szAbsolutePath);
    size_t iLength = strlen(szFilename);

    // Filename without extension.
    char szRawName[PLATFORM_MAX_PATH];
    memset(szRawName, '\0', sizeof(szRawName));
    strncpy(szRawName, szFilename, iLength - 3);
    szRawName[iLength - 3] = '\0';

    // Import Python module (potential plugin).
    PyObject *pName = PyUnicode_DecodeFSDefault(szRawName);
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule != NULL)
    {
        if (CPyPlugin::IsValid(pModule))  // Module has PYSMOD_PLUGIN attribute?
        {
            CPyPlugin *pPlugin = new CPyPlugin(pModule, szRawName, szAbsolutePath, szRelativePath);
            this->m_plugins.push_back(pPlugin);
        }
    }
}

void CPyPluginManager::UnloadAll()
{
    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        delete this->m_plugins[i];  // This will call Py_DECREF for each module.
    }
    std::vector<CPyPlugin *>().swap(this->m_plugins);
}

//
// # Python examples:
// def OnPluginStart():
//     LogMessage(f'Plugin has been started.')
//
void CPyPluginManager::Call_OnPluginStart()
{
    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        PyObject* pFunc = NULL;
        PyObject* pResult = NULL;

        pFunc = PyObject_GetAttrString(this->m_plugins[i]->GetModule(), "OnPluginStart");
        if (pFunc && PyCallable_Check(pFunc))
        {
            pResult = PyObject_CallFunction(pFunc, NULL);
            LogPythonErrorIfAny();
        }

        Py_XDECREF(pResult);
        Py_XDECREF(pFunc);
    }
}

//
// # Python examples:
// def OnPluginEnd():
//     LogMessage(f'Plugin is now terminating.')
//
void CPyPluginManager::Call_OnPluginEnd()
{
    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        PyObject* pFunc = NULL;
        PyObject* pResult = NULL;

        pFunc = PyObject_GetAttrString(this->m_plugins[i]->GetModule(), "OnPluginEnd");
        if (pFunc && PyCallable_Check(pFunc))
        {
            pResult = PyObject_CallFunction(pFunc, NULL);
            LogPythonErrorIfAny();
        }

        Py_XDECREF(pResult);
        Py_XDECREF(pFunc);
    }
}

//
// # Python examples:
// def OnEntityCreated(entity, classname):
//     LogMessage(f'Entity created: {entity}, classname: {classname}')
//
void CPyPluginManager::Call_OnEntityCreated(CBaseEntity* pEntity, const char* classname)
{
    //int ref = gamehelpers->EntityToBCompatRef(pEntity);
    //int index = gamehelpers->ReferenceToIndex(ref);

    //int index = gamehelpers->EntityToBCompatRef(pEntity);
    //if (index < 0 || index >= MAX_EDICTS)
    //    return;

    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        PyObject* pFunc = NULL;
        PyObject* pResult = NULL;

        pFunc = PyObject_GetAttrString(this->m_plugins[i]->GetModule(), "OnEntityCreated");
        if (pFunc && PyCallable_Check(pFunc))
        {
            int ref = gamehelpers->EntityToBCompatRef(pEntity);
            pResult = PyObject_CallFunction(pFunc, "is", ref, classname);
            LogPythonErrorIfAny();
        }

        Py_XDECREF(pResult);
        Py_XDECREF(pFunc);
    }
}

//
// # Python examples:
// def OnEntityDestroyed(entity):
//     LogMessage(f'Entity deleted: {entity}')
//
void CPyPluginManager::Call_OnEntityDestroyed(CBaseEntity* pEntity)
{
    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        PyObject* pFunc = NULL;
        PyObject* pResult = NULL;

        pFunc = PyObject_GetAttrString(this->m_plugins[i]->GetModule(), "OnEntityDestroyed");
        if (pFunc && PyCallable_Check(pFunc))
        {
            int ref = gamehelpers->EntityToBCompatRef(pEntity);
            pResult = PyObject_CallFunction(pFunc, "i", ref);
            LogPythonErrorIfAny();
        }

        Py_XDECREF(pResult);
        Py_XDECREF(pFunc);
    }
}

//
// # Python examples:
// def OnClientPutInServer(client):
//     LogMessage(f'Client {client} entered the server.')
//
void CPyPluginManager::Call_OnClientPutInServer(int client)  // declared in IClientListener
{
    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        PyObject* pFunc = NULL;
        PyObject* pResult = NULL;

        pFunc = PyObject_GetAttrString(this->m_plugins[i]->GetModule(), "OnClientPutInServer");
        if (pFunc && PyCallable_Check(pFunc))
        {
            pResult = PyObject_CallFunction(pFunc, "i", client);
            LogPythonErrorIfAny();
        }

        Py_XDECREF(pResult);
        Py_XDECREF(pFunc);
    }
}

//
// # Python examples:
// count = 5
// def OnGameFrame():
//     global count
//     if count > 0:
//         LogMessage('OnGameFrame: This message will be displayed 5 times.')
//         count -= 1
//
void CPyPluginManager::Call_OnGameFrame()
{
    for (int i = 0; i < this->m_plugins.size(); i++)
    {
        PyObject* pFunc = NULL;
        PyObject* pResult = NULL;

        pFunc = PyObject_GetAttrString(this->m_plugins[i]->GetModule(), "OnGameFrame");
        if (pFunc && PyCallable_Check(pFunc))
        {
            pResult = PyObject_CallFunction(pFunc, NULL);
            LogPythonErrorIfAny();
        }

        Py_XDECREF(pResult);
        Py_XDECREF(pFunc);
    }
}


//--------------------------------------------------------------------//
// CPySMod                                                            //
//--------------------------------------------------------------------//
CPySMod::~CPySMod()
{
    this->m_bIsRunning = false;
    delete this->m_pPluginManager;

    // Finishes the interpreter.
    if (Py_FinalizeEx() == -1)
    {
        g_pSM->LogError(myself, "Something went wrong when finalizing the Python interpreter.");
    }
}

bool CPySMod::Initialize()
{
    if (this->IsRunning())
    {
        return true;
    }

    Py_Initialize();
    if (!Py_IsInitialized())
    {
        g_pSM->LogError(myself, "Could not initialize the Python interpreter.");
        return false;
    }

    this->m_bIsRunning = true;
    this->PreparePackaging();
    this->m_pPluginManager = new CPyPluginManager;

    return true;
}

bool CPySMod::IsRunning()
{
    return this->m_bIsRunning;
}

CPyPluginManager *CPySMod::GetPluginManager()
{
    return this->m_pPluginManager;
}

void CPySMod::PreparePackaging()
{
    // A little hack for packaging.
    // This should be after Py_Inicialize()
    PyRun_SimpleString(
        "import importlib.abc\n"
        "import importlib.machinery\n"
        "import sys\n"
        "\n"
        "\n"
        "class Finder(importlib.abc.MetaPathFinder):\n"
        "    def find_spec(self, fullname, path, target=None):\n"
        "        if fullname in sys.builtin_module_names:\n"
        "            return importlib.machinery.ModuleSpec(\n"
        "                fullname,\n"
        "                importlib.machinery.BuiltinImporter,\n"
        "            )\n"
        "\n"
        "\n"
        "sys.meta_path.append(Finder())\n"
    );
}
