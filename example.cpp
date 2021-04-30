#include "helper.hpp"

int main() {
    if (Python::Get().Initialize("Test")) {
        Python::Get().File("test.py");
        Python::Get().End();
    }

    return 0;
}