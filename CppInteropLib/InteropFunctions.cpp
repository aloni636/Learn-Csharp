#include "pch.h"

// Ensure function names are not mangled by C++
extern "C" {
    __declspec(dllexport) int AddNumbers(int a, int b) {
        return a + b;
    }
}