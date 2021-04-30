# pypp (x64)
Python code emulator on C++

> The 64-bit version for [Python](https://www.python.org/) was used here

## Syntax:
```
  Python::Get().Initialize("Test") - Init python script (return boolean)
  Python::Get().End() - End python script
  Python::Get().File("test.py") - Open python file
```

## Example:
example.cpp:
```cpp
  #include "helper.hpp"

  int main() {
    if (Python::Get().Initialize("Test")) {
      Python::Get().File("test.py");
      Python::Get().End();
    }
    return 0;
  }
```
test.py from [Fortnite-ItemShop](https://github.com/s3nk0s4n/Fortnite-ItemShop/blob/main/main.py)

Output:

![](https://i.imgur.com/VbhWErT.png)
