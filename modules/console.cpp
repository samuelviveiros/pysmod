#include "console.h"

//
// Python examples:
//   some_player = 1
//   PrintToConsole(1, 'Hello from Python!')
//
// addons\sourcemod\plugins\include\console.inc
// smsdk-1.7.2\core\logic\smn_console.cpp
// smsdk-1.7.2\core\PlayerManager.cpp
PyObject* sm_PrintToConsole(PyObject* self, PyObject* args)
{
    int index = 0;
    char *message = NULL;

    if (!PyArg_ParseTuple(args, "is:PrintToConsole", &index, &message))
    {
        return NULL;
    }

    if ((index < 0) || (index > playerhelpers->GetMaxClients()))
    {
        PyErr_Format(PyExc_IndexError, "Client index %d is invalid", index);
        return NULL;
    }

    IGamePlayer* pPlayer = NULL;
    if (index != 0)
    {
        pPlayer = playerhelpers->GetGamePlayer(index);
        if (!pPlayer->IsInGame())
        {
            PyErr_Format(PyExc_Exception, "Client %d is not in game", index);
            return NULL;
        }

        // Silent fail on bots, engine will crash
        if (pPlayer->IsFakeClient())
        {
            Py_RETURN_NONE;
        }
    }

    char buffer[1024];
    smutils->Format(buffer, sizeof(buffer), "%s\n", message);

    if (index != 0)
    {
        pPlayer->PrintToConsole(message);
    }
    //else {
    //    smcore.ConPrint(message);  // Print to server console?
    //}

    Py_RETURN_NONE;
}

PyObject* PyInit_console(void)
{
    PyObject *pModule = PyModule_Create(&ConsoleModule);
    return pModule;
}
