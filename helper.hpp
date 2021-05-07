//https://docs.python.org/3/extending/embedding.html
#define PY_SSIZE_T_CLEAN
#define MAX_SIZE 255

#include <Python.h>
#pragma comment(lib, "python39.lib")
#pragma comment(lib, "python3.lib")
#pragma comment(lib, "_tkinter.lib")

#include "singleton.hpp"
#include <string>

using namespace std;

//static PyObject* ModuleError;
static PyMethodDef ModuleMethods[MAX_SIZE];
static struct PyModuleDef py_module;
static int pos = 0;
static string module_name;

class Python : public Singleton<Python> {
    friend class Singleton<Python>;
private:
    wchar_t* program;
public:
    //module functions
    void AddFunction(const char* f_name, static PyObject* function(PyObject*, PyObject*)) {
        ModuleMethods[pos] = { f_name, function, METH_VARARGS, NULL };
        pos++;
    }
    void CreateModule(const char* c_module_name) {
        module_name = c_module_name;
        ModuleMethods[pos] = { NULL, NULL, 0, NULL };
        py_module = { PyModuleDef_HEAD_INIT, module_name.c_str(), NULL, -1, ModuleMethods, NULL, NULL, NULL, NULL };
    }
    static PyObject* PyInitModule(void) {
        PyObject* m;

        m = PyModule_Create(&py_module);
        if (m == NULL)
            return NULL;

        return m;
    }
    //main functions
    bool Initialize(const char* name, bool c_module) {
        program = Py_DecodeLocale(name, NULL);
        if (program == NULL) {
            fprintf(stderr, "Fatal error: cannot decode str\n");
            return false;
        }
        Py_SetProgramName(program);

        if (c_module)
            if (PyImport_AppendInittab(module_name.c_str(), PyInitModule) == -1) {
                fprintf(stderr, "Error: could not extend in-built modules table\n");
                return false;
            }

        Py_Initialize();
        return true;
    }
    void End() {
        if (Py_FinalizeEx() < 0)
            exit(120);
        PyMem_RawFree(program);
    }
    //py functions
    void SimpleString(const char* sstring) {
        PyRun_SimpleString(sstring);
    }
    void File(const char* filename) {
        FILE* file = _Py_fopen_obj(Py_BuildValue("s", filename), "r+");
        if (file != NULL)
            PyRun_SimpleFile(file, filename);
    }
};