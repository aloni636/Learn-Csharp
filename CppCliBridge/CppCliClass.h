#pragma once

using namespace System;

namespace CppCli {  // The namescape being used when including C++ in C#, i.e. `using CppCli`
    public ref class CppCliClass {
    public:
        CppCliClass();
        String^ GetMessage();
    };
}