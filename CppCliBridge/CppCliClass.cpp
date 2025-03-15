#include "pch.h"
#include "CppCliClass.h"
#include <iostream>
#include <string>
#include <msclr/marshal_cppstd.h>  // for converting between .NET types and native CPP types
#include <array>  // for std::array 
#include <algorithm>
#include <sstream>  // for stringstream

namespace CppCli {  
    CppCliClass::CppCliClass() {}

    String^ CppCliClass::GetString() {  // ^ is called a handler, as opposed to C/C++ pointer (*) or reference (&)
        return "Hello from C++/CLI!";
    };
    int CppCliClass::GetInt() { return 42; }
    double CppCliClass::GetDouble() { return 3.1415; }  // defaults to double literal; ref: https://learn.microsoft.com/en-us/cpp/cpp/numeric-boolean-and-pointer-literals-cpp?view=msvc-170#floating-point-literals
    int CppCliClass::IntDivision(int a, int b) { return a / b; }
    bool CppCliClass::IsPositive(int x) { return x > 0;  }
    
    /**
     * @brief Append string a to string b using C++
     * @param a string a to append
     * @param b string b to append
     * @return Managed string after being appended
     */
    String^ CppCliClass::AppendStrings(String^ a, String^ b) {
        std::string aCpp = msclr::interop::marshal_as<std::string>(a);
        std::string bCpp = msclr::interop::marshal_as<std::string>(b);
        std::cout << "[C++]: Appending \"" << bCpp << "\" to \"" << aCpp << "\"\n";
        std::string appendedString = aCpp + bCpp;
        String^ managedString = gcnew String(appendedString.c_str());
        return managedString;
    };

    String^ CppCliClass::GetUTF16String() {
        const std::wstring utf16String = L"Hello UTF16";
        String^ managedUTF16String = gcnew String(utf16String.c_str());
        return managedUTF16String;
    };

    array<int>^ CppCliClass::GetFixedArray() {
        array<int>^ managedArray = gcnew array<int> {1, 2, 3, 4, 5};
        return managedArray;
    }

    void CppCliClass::ClampIntElements(array<int>^% managedArray, int min, int max) {  // ^% is a managed reference handler
        size_t managedArraySize = managedArray->Length;
        for (int i = 0; i < managedArraySize; i++) {
            int element = managedArray[i];
            managedArray[i] = std::clamp(element, min, max);
        }
    }

    List<int>^ CppCliClass::GetDynamicArray(size_t size) {
        List<int>^ managedVector = gcnew List<int>(size);
        for (int i = 0; i < size;i++) {
            managedVector->Add(i);
        }
        return managedVector;
    }
    void CppCliClass::AppendIntToArray(List<int>^% vec, int element) {
        vec->Add(element);
    };

    // Overloading works between CPP and C#
    ManagedStruct CppCliClass::GetStruct(int X, int Y, String^ Content) {
        ManagedStruct out;
        out.X = 0;
        out.Y = 0;
        out.Content = Content;
        return out;
    }
    ManagedStruct CppCliClass::GetStruct() {
        return GetStruct(0,0,"Empty");
    }
    String^ CppCliClass::StructAsString(ManagedStruct managedStruct) {
        std::stringstream ss;
        ss << "{X: " << managedStruct.X << ", Y: " << managedStruct.Y << ", Content: \"" << msclr::interop::marshal_as<std::string>(managedStruct.Content) << "\"}";
        return gcnew String(ss.str().c_str());
    };
    
    // Calling C# from C++/CLI
    int CppCliClass::CSharpCachedRecursiveFactorial(int factorial) {
        return CSharpCli::CSharpClass().CachedRecursiveFactorial(factorial);
    }
    CSharpClass^ CppCliClass::GetCSharpClass() {
        return gcnew CSharpClass();
    }

    // Native class wrapper
    ManagedRandomNumberGenerator::ManagedRandomNumberGenerator(int seed, int min, int max) {
        this->nativeObj = new RandomNumberGenerator(seed, min, max);
    }
    ManagedRandomNumberGenerator::ManagedRandomNumberGenerator(int min, int max) {
        this->nativeObj = new RandomNumberGenerator(min, max);
    }
    int ManagedRandomNumberGenerator::generate() {
        return this->nativeObj->generate();
    }
    ManagedRandomNumberGenerator::~ManagedRandomNumberGenerator() {
        std::cout << "[C++/CLI]: Deleting RandomNumberGenerator.\n";
        delete this->nativeObj;
    }
}
