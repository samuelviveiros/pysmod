#include "sourcemod.h"


PyObject* PyInit_sourcemod(void)
{
    PyObject *pModule = PyModule_Create(&SourcemodModule);
    PyModule_AddObject(pModule, "__path__", Py_BuildValue("()"));  // For packaging.
    return pModule;
}
