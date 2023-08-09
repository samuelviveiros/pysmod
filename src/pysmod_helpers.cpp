#include "pysmod_helpers.h"


void LogPythonErrorIfAny(void) {
    if (PyErr_Occurred() == NULL)
    {
        return;
    }

    PyObject *pType = NULL, *pValue = NULL, *pTraceback = NULL;
    PyObject *pModule = NULL, *pModuleName = NULL;

    PyErr_Fetch(&pType, &pValue, &pTraceback);
    PyErr_NormalizeException(&pType, &pValue, &pTraceback);

    pModuleName = PyUnicode_FromString("traceback");
    pModule = PyImport_Import(pModuleName);
    Py_DECREF(pModuleName);
    if (pModule == NULL)
    {
        g_pSM->LogError(myself, "LogPythonErrorIfAny: Could not import 'traceback' module.");
        return;
    }

    PyObject *pFunc = NULL;
    pFunc = PyObject_GetAttrString(pModule, "format_exception");
    if (pFunc == NULL)
    {
        g_pSM->LogError(myself, "LogPythonErrorIfAny: Could not find 'format_exception' function.");
        Py_DECREF(pModule);
        return;
    }

    if (!PyCallable_Check(pFunc))
    {
        g_pSM->LogError(myself, "LogPythonErrorIfAny: Object 'format_exception' is not callable.");
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        return;
    }

    PyObject *pFormatted = NULL;
    pFormatted = PyObject_CallFunctionObjArgs(
        pFunc,
        (pType != NULL ? pType : Py_None),
        (pValue != NULL ? pValue : Py_None),
        (pTraceback != NULL ? pTraceback : Py_None),
        NULL
    );

    Py_XDECREF(pType);
    Py_XDECREF(pValue);
    Py_XDECREF(pTraceback);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    if (pFormatted == NULL)
    {
        LogPythonError();
        g_pSM->LogError(myself, "LogPythonErrorIfAny: Something went wrong when calling 'format_exception'.");
        return;
    }

    if (!PyList_Check(pFormatted))
    {
        g_pSM->LogError(myself, "LogPythonErrorIfAny: Result from 'format_exception' is not a List.");
        Py_DECREF(pFormatted);
        return;
    }

    Py_ssize_t len = PyList_Size(pFormatted);
    PyObject *pItem = NULL;
    const char *line = NULL;
    char *buffer = (char*)malloc(4096);
    memset(buffer, '\0', 4096);
    strcpy(buffer, "!!!ERROR!!!\n");
    for (Py_ssize_t i = 0; i < len; i++)
    {
        pItem = PyList_GetItem(pFormatted, i);
        Py_INCREF(pItem);
        line = PyUnicode_AsUTF8(pItem);
        strncat(buffer, line, strlen(line));
        Py_DECREF(pItem);
        pItem = NULL;
    }
    g_pSM->LogError(myself, "%s", buffer);
    free(buffer);

    Py_DECREF(pFormatted);
}

void LogPythonError(void)
{
    if (PyErr_Occurred() != NULL)
    {
        PyObject *pType = NULL, *pValue = NULL, *pTraceback = NULL;
        PyObject *pStr1 = NULL, *pStr2 = NULL;

        PyErr_Fetch(&pType, &pValue, &pTraceback);
        PyErr_NormalizeException(&pType, &pValue, &pTraceback);
        if (pType == NULL
            || pValue == NULL
            || ((pStr1 = PyObject_Str(pType)) == NULL)
            || ((pStr2 = PyObject_Str(pValue)) == NULL))
        {
            Py_XDECREF(pStr1);
            Py_XDECREF(pStr2);
            Py_XDECREF(pType);
            Py_XDECREF(pValue);
            Py_XDECREF(pTraceback);
            return;
        }

        //g_pSM->LogError(myself, "PythonError: %s: %s", PyUnicode_AsUTF8(pStr1), PyUnicode_AsUTF8(pStr2));
        g_pSM->LogError(myself, "PythonError:\n\t%s\n\t%s", PyUnicode_AsUTF8(pStr1), PyUnicode_AsUTF8(pStr2));
    }
}

void GetPySModPath(char *destination, size_t maxlength)
{
    char pysmod_path[PLATFORM_MAX_PATH];
    memset(pysmod_path, '\0', sizeof(pysmod_path));
    g_pSM->BuildPath(Path_SM, pysmod_path, sizeof(pysmod_path), "plugins/pysmod");
    strncpy(destination, pysmod_path, maxlength);
}

void Wrap_PyModuleAddIntConstant(PyObject* module, const char* name, long value)
{
    if (PyModule_AddIntConstant(module, name, value) == -1)
    {
        LogPythonErrorIfAny();
        g_pSM->LogError(myself, "Error calling PyModule_AddIntConstant with args: name = %s, value = %ld", name, value);
    }
}
