#ifndef _PYSMOD_HELPERS_H_
#define _PYSMOD_HELPERS_H_


#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif
#include <Python.h>
#include "sdk/smsdk_ext.h"


void LogPythonError(void);
void LogPythonErrorIfAny(void);
void GetPySModPath(char *destination, size_t maxlength);
void Wrap_PyModuleAddIntConstant(PyObject* module, const char* name, long value);


#endif  //_PYSMOD_HELPERS_H_
