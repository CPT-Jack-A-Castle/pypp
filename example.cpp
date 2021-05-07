#include "helper.hpp"

static PyObject* GetBool(PyObject* self, PyObject* args)
{
    const char* command;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    return PyBool_FromLong(atol(command));
}

int main() {
    Python::Get().AddFunction("GetBool", GetBool);
    Python::Get().CreateModule("ExampleModule");

    if (Python::Get().Initialize("Test", true)) {
        Python::Get().File("test.py");
        Python::Get().SimpleString("import ExampleModule\nprint(ExampleModule.GetBool('0'))");
        Python::Get().End();
    }

    return 0;
}