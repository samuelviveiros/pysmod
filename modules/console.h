#ifndef _PYSMOD_CONSOLE_MODULE_H_
#define _PYSMOD_CONSOLE_MODULE_H_


#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include "sdk/smsdk_ext.h"
#include "pysmod_helpers.h"


PyObject* sm_PrintToConsole(PyObject* self, PyObject* args);
PyObject* PyInit_console(void);


static PyMethodDef ConsoleMethods[] = {
    { "PrintToConsole", sm_PrintToConsole, METH_VARARGS, "N/A" },
    {NULL, NULL, 0, NULL}
};

static PyModuleDef ConsoleModule = {
    PyModuleDef_HEAD_INIT, "console", NULL, -1, ConsoleMethods,
    NULL, NULL, NULL, NULL
};


#endif  //_PYSMOD_CONSOLE_MODULE_H_
