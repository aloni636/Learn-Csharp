// DLLConsumer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "MathLib.h"  // Make sure to include the inclosing folder of the DLL header file: (Right click) Project -> Properties -> C/C++ -> General -> Additional Include Directories

// NOTE: After you built the MathDLL.dll and the DLLConsumer.exe, you can experience how Windows handles missing DLL by:
// A. Opening ..\\..\\x64
// B. Renaming MathDLL.dll to MathDLL.dll1
// C. Right clicking DLLConsumer.exe
// An system error message should pop up: 
// "The code execution cannot proceed because MathDLL.dll was not found.Reinstalling the program may fix this problem."

int main()
{
    std::cout << "Hello, C++ DLL Consumer!\n";
    MathLib::AddNumbers(1, 2);
    MathLib::AddNumbers(1.1, 2.1);
    MathLib::AddNumbers(1.1f,2.1f);
}
