// NOTE: Whenever modifying the CPP code, a build of the CPP/CLI project is required.
#pragma once

using namespace System;

namespace CppCli {  // The namespace being used when including C++ in C#, i.e. `using CppCli`
    public ref class CppCliClass {
    public:
        CppCliClass();
        String^ GetString();
        int GetInt();
        double GetDouble();
        int IntDivision(int a, int b);
        bool IsPositive(int x);
    };
}