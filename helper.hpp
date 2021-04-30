//https://docs.python.org/3/extending/embedding.html
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#pragma comment(lib, "python39.lib")
#pragma comment(lib, "python3.lib")
#pragma comment(lib, "_tkinter.lib")

#include "singleton.hpp"
#include <string>

using namespace std;

class Python : public Singleton<Python> {
    friend class Singleton<Python>;
private:
    wchar_t* program;
    void InitModule() {

    }
public:
    //main functions
    bool Initialize(string name) {
        program = Py_DecodeLocale(name.c_str(), NULL);
        if (program == NULL) {
            fprintf(stderr, "Fatal error: cannot decode str\n");
            return false;
        }
        Py_SetProgramName(program);
        Py_Initialize();
        return true;
    }
    void End() {
        if (Py_FinalizeEx() < 0)
            exit(120);
        PyMem_RawFree(program);
    }
    //custom functions
    void SimpleString(string filename) {
        PyRun_SimpleString(filename.c_str());
    }
    void File(string filename) {
        FILE* file = _Py_fopen_obj(Py_BuildValue("s", filename), "r+");
        if (file != NULL)
            PyRun_SimpleFile(file, filename.c_str());
    }
    /*void CreateModule(string modulename, static PyMethodDef methods[]) {
        PyModuleDef Module = { PyModuleDef_HEAD_INIT, modulename.c_str(), NULL, -1, methods, NULL, NULL, NULL, NULL };
        PyModule_Create(&Module);
    }*/
};
