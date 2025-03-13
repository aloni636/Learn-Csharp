// NOTE: I use post build events CppInteropLib Project Properties -> Build Events -> Post-Build Events -> Command Line
#include "pch.h"

// TODO 1: (DONE): Basic interop
// TODO 2: (NOT POSSIBLE, REJECTED in favor of C++/CLI) Use STD types like std::string, std::vector, std::map, std::set etc
// TODO 3: (REJECTED in favor of C++/CLI) Use custom defined structs
// TODO 4: (REJECTED in favor of C++/CLI) Explore using templated definitions like min and max
// TODO 5: (REJECTED in favor of C++/CLI) Use custom defined cpp class with simple state

// Ensure function names are not mangled by C++
extern "C" {
    __declspec(dllexport) int AddNumbers(int a, int b) {
        return a + b;
    };
    //__declspec(dllexport) 
}