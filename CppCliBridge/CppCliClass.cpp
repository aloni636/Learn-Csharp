#include "pch.h"
#include "CppCliClass.h"

namespace CppCli {
    CppCliClass::CppCliClass() {}

    String^ CppCliClass::GetMessage() {
        return "Hello from C++/CLI!";
    }
}
