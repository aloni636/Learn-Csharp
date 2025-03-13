#include "pch.h"
#include "CppCliClass.h"

namespace CppCli {
    CppCliClass::CppCliClass() {}

    String^ CppCliClass::GetString() {
        return "Hello from C++/CLI!";
    };
    int CppCliClass::GetInt() { return 42; }
    double CppCliClass::GetDouble() { return 3.1415; }  // defaults to double literal; ref: https://learn.microsoft.com/en-us/cpp/cpp/numeric-boolean-and-pointer-literals-cpp?view=msvc-170#floating-point-literals
    int CppCliClass::IntDivision(int a, int b) { return a / b; }
    bool CppCliClass::IsPositive(int x) { return x > 0;  }

}
