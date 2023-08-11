#include "files.h"


//
// Python example:
//   built_path = BuildPath(Path_SM, 'plugins/combine')
//   LogMessage(built_path)
//
PyObject* sm_BuildPath(PyObject* self, PyObject* args)
{
    PathType path_type = Path_None;
    char *path = NULL;

    if (!PyArg_ParseTuple(args, "is:BuildPath", &path_type, &path))
    {
        return NULL;
    }

    char built_path[PLATFORM_MAX_PATH];
    g_pSM->BuildPath(path_type, built_path, sizeof(built_path), path);

    return PyUnicode_FromString(built_path);
}

PyObject* PyInit_files(void)
{
    PyObject *pModule = PyModule_Create(&FilesModule);

    Wrap_PyModuleAddIntConstant(pModule, "Path_SM", 2);  // SourceMod root folder.
    Wrap_PyModuleAddIntConstant(pModule, "PLATFORM_MAX_PATH", PLATFORM_MAX_PATH);  // Maximum path length.

    return pModule;
}
