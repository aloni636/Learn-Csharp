// NOTE: Whenever modifying the CPP code, a build of the CPP/CLI project is required.
#pragma once
#include "pch.h"
#include "NativeClass.h"  // Includes RandomNumberGenerator
#include <msclr/marshal_cppstd.h>  // For conversions

using namespace System;
using namespace System::Collections::Generic;  // for List type

namespace CppCli {  // The namespace being used when including C++ in C#, i.e. `using CppCli`
    public value struct ManagedStruct {  // value struct behaves like C# struct which is stack allocated
    public:
        int X;
        int Y;
        String^ Content;
    };
    public ref class CppCliClass {  // ref means it is managed by cpp/cli
    public:
        CppCliClass();
        
        String^ GetString();
        int GetInt();
        double GetDouble();
        int IntDivision(int a, int b);
        bool IsPositive(int x);
        
        String^ AppendStrings(String^ a, String^ b);

        String^ GetUTF16String();

        array<int>^ GetFixedArray();
        void ClampIntElements(array<int>^%, int min, int max);  // ^% is a managed reference handler
        List<int>^ GetDynamicArray(size_t size);
        void AppendIntToArray(List<int>^% vec, int element);

        ManagedStruct GetStruct(int X, int Y, String^ Content);
        ManagedStruct GetStruct();
        String^ StructAsString(ManagedStruct managedStruct);
    };
    
    // Native class wrapper
    public ref class ManagedRandomNumberGenerator {
    private:
        RandomNumberGenerator* nativeObj;
    public:
        // Constructors (Overloaded)
        ManagedRandomNumberGenerator(int seed, int min, int max);
        ManagedRandomNumberGenerator(int min, int max);
        ~ManagedRandomNumberGenerator(); // Destructor
        int generate();
    };
}