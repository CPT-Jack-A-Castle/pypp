# pypp (x32)
Python code player on C++

> The 32-bit version for [Python](https://www.python.org/) was used here
> 
> You must copy python dll file from "dlls" folder to your release folder

## Syntax:
```
  Python::Get().Initialize("Test", false) - Init python script (return boolean)
  Python::Get().SimpleString("print('Hello World!')") - Code from string
  Python::Get().End() - End python script
  Python::Get().File("test.py") - Open python file
  Python::Get().AddFunction("FunctionName", Function); - Add function to module
  Python::Get().CreateModule("ExampleModule"); - Create module
```

## Module example:
example.cpp:
```cpp
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
      Python::Get().SimpleString("import ExampleModule\nprint(ExampleModule.GetBool('0'))");
      Python::Get().End();
    }
    return 0;
  }
```

## File example:
example.cpp:
```cpp
  #include "helper.hpp"

  int main() {
    if (Python::Get().Initialize("Test", false)) {
      Python::Get().File("test.py");
      Python::Get().End();
    }
    return 0;
  }
```
test.py from [Fortnite-ItemShop](https://github.com/s3nk0s4n/Fortnite-ItemShop/blob/main/main.py)

Output:

![](https://i.imgur.com/VbhWErT.png)
