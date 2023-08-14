#ifndef _PYSMOD_H_
#define _PYSMOD_H_

#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include <vector>
#include "sdk/smsdk_ext.h"
#include "pysmod_helpers.h"


#define PLUGIN_INFO_SIZE 5

class CPyPluginInfo
{
public:
    CPyPluginInfo(PyObject *pModule, const char *pModuleName);
    ~CPyPluginInfo();
public:
    const char *GetAuthor();
    const char *GetDescription();
    const char *GetName();
    const char *GetUrl();
    const char *GetVersion();
    bool IsValid();
private:
    char m_sAuthor[256];
    char m_sDescription[256];
    bool m_bIsValid = false;
    PyObject *m_pModule = NULL;
    char m_sModuleName[256];
    char m_sName[256];
    char m_sUrl[256];
    char m_sVersion[256];
private:
    bool Read();
    void ClearInfo();
};


class CPyPlugin
{
public:  // constructors and destructors
    CPyPlugin(PyObject *pModule, const char *pModuleName, const char *pAbsolutePath, const char *pRelativePath);
    ~CPyPlugin();
public:
    static bool IsValid(PyObject *pModule);
public:
    CPyPluginInfo *GetInfo();
    PyObject *GetModule();
    const char *GetModuleName();
    const char *GetAbsolutePath();
    const char *GetRelativePath();
private:  // data members
    PyObject *m_pModule = NULL;
    CPyPluginInfo *m_pPluginInfo = NULL;
    char m_sModuleName[256];
    char m_sAbsolutePath[PLATFORM_MAX_PATH];
    char m_sRelativePath[PLATFORM_MAX_PATH];
};


class CPyPluginManager
{
public:
    CPyPluginManager();
    ~CPyPluginManager();
public:
    void AddToPythonPath(const char *pszPath);
    void LoadPluginsFromDir(const char *pszBaseDir, const char *pszLocalPath);
    void LoadPlugin(const char *szAbsolutePath, const char *szRelativePath);
    void UnloadAll();
public:
    void Call_OnEntityCreated(CBaseEntity* pEntity, const char* classname);
    void Call_OnEntityDestroyed(CBaseEntity* pEntity);
    void Call_OnClientPutInServer(int client);
    void Call_OnPluginStart();
    void Call_OnPluginEnd();
    void Call_OnGameFrame();
private:
    std::vector<CPyPlugin *> m_plugins;
    PyObject *m_pSysModule = NULL;
    PyObject *m_pPathList = NULL;
};


class CPySMod
{
public:
    CPySMod() {};
    ~CPySMod();
public:
    bool Initialize();
    bool IsRunning();
    void logPythonVersion();
    CPyPluginManager *GetPluginManager();
private:
    bool m_bIsRunning = false;
    CPyPluginManager *m_pPluginManager = NULL;
private:
    void PreparePackaging();
};

#endif  // _PYSMOD_H_
