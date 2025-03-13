#include "pch.h"
#include "CppCliClass.h"
#include <iostream>
#include <string>
#include <msclr/marshal_cppstd.h>  // for converting between .NET types and native CPP types

namespace CppCli {
    CppCliClass::CppCliClass() {}

    String^ CppCliClass::GetString() {
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
        std::cout << "C++: Appending \"" << bCpp << "\" to \"" << aCpp << "\"\n";
        std::string appendedString = aCpp + bCpp;
        String^ managedString = gcnew String(appendedString.c_str());
        return managedString;
    }
}
