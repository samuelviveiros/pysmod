#ifndef _PYSMOD_FILE_MODULE_H_
#define _PYSMOD_FILE_MODULE_H_


#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include "sdk/smsdk_ext.h"
#include "pysmod_helpers.h"


PyObject* sm_BuildPath(PyObject* self, PyObject* args);
PyObject* PyInit_files(void);


const char doc_BuildPath[] = { (
    "BuildPath(path_type, format) -> str\n"
    "\n"
    "Builds a platform path for a specific target base path.\n"
    "\n"
    "If the path starts with the string \"file://\" and the PathType "
    "is not relative, then the \"file://\" portion is stripped off, and "
    "the rest of the path is used without any modification (except for "
    "correcting slashes). This can be used to override the path builder "
    "to supply alternate absolute paths. Examples:\n"
    "\n"
    "file://C:/Temp/file.txt\n"
    "file:///tmp/file.txt\n"
    "\n"
    "path_type (int):  Type of path to use as a base.\n"
    "path (str):       Path to be concatenated.\n"
    "return (str):     The built path.\n"
) };


static PyMethodDef FilesMethods[] = {
    { "BuildPath", sm_BuildPath, METH_VARARGS, "N/A" },
    {NULL, NULL, 0, NULL}
};

static PyModuleDef FilesModule = {
    PyModuleDef_HEAD_INIT, "files", NULL, -1, FilesMethods,
    NULL, NULL, NULL, NULL
};


#endif  //_PYSMOD_FILE_MODULE_H_
