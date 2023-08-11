#include "logging.h"


//
// Python examples:
//   LogMessage('Hello from Python!')
//   name = 'Zoey'
//   LogMessage(f'Hello {name}, how are you?')
//
PyObject* sm_LogMessage(PyObject* self, PyObject* args)
{
    char* message = NULL;

    if (!PyArg_ParseTuple(args, "s:LogMessage", &message))
    {
        return NULL;
    }

    g_pSM->LogMessage(myself, "%s", message);

    Py_RETURN_NONE;
}

//
// Python examples:
//   LogError('Hello from Python!')
//   name = 'Zoey'
//   LogError(f'Hello {name}, how are you?')
//
PyObject* sm_LogError(PyObject* self, PyObject* args)
{
    char* message = NULL;

    if (!PyArg_ParseTuple(args, "s:LogError", &message))
    {
        return NULL;
    }

    g_pSM->LogError(myself, "%s", message);

    Py_RETURN_NONE;
}

PyObject* PyInit_logging(void)
{
    PyObject *pModule = PyModule_Create(&LoggingModule);
    return pModule;
}
