#ifndef _PYSMOD_SOURCEMOD_MODULE_H_
#define _PYSMOD_SOURCEMOD_MODULE_H_


#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include "sdk/smsdk_ext.h"
#include "pysmod_helpers.h"


PyObject* PyInit_sourcemod(void);


static PyMethodDef SourcemodMethods[] = {
    {NULL, NULL, 0, NULL}
};

static PyModuleDef SourcemodModule = {
    PyModuleDef_HEAD_INIT, "sourcemod", NULL, -1, SourcemodMethods,
    NULL, NULL, NULL, NULL
};


#endif  //_PYSMOD_SOURCEMOD_MODULE_H_
