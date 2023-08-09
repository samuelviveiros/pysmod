#ifndef _PYSMOD_LOGGING_MODULE_H_
#define _PYSMOD_LOGGING_MODULE_H_


#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include "sdk/smsdk_ext.h"
#include "pysmod_helpers.h"


PyObject* sm_LogMessage(PyObject* self, PyObject* args);
PyObject* sm_LogError(PyObject* self, PyObject* args);
PyObject* PyInit_logging(void);


const char doc_LogMessage[] = { (
    "LogMessage(message) -> None\n"
    "\n"
    "Logs a message to the SourceMod logs.\n"
    "\n"
    "message (str): The message to be logged.\n"
) };

const char doc_LogError[] = { (
    "LogError(message) -> None\n"
    "\n"
    "Logs a message to the SourceMod error logs.\n"
    "\n"
    "message (str): The message to be logged.\n"
) };


static PyMethodDef LoggingMethods[] = {
    { "LogMessage", sm_LogMessage, METH_VARARGS, "N/A" },
    { "LogError", sm_LogError, METH_VARARGS, "N/A" },
    {NULL, NULL, 0, NULL}
};

static PyModuleDef LoggingModule = {
    PyModuleDef_HEAD_INIT, "logging", NULL, -1, LoggingMethods,
    NULL, NULL, NULL, NULL
};


#endif  //_PYSMOD_LOGGING_MODULE_H_
