// DynamicDLLConsumer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <windows.h>
#include <iostream>

// function signature type:
// typedef <return type> (*<custom type name>)(<argument 1>, <argument 2> ... <argument N>)
typedef int (CALLBACK *INTS_ADD_NUMBERS)(int, int);

int main()
{
    // Ref: https://stackoverflow.com/a/8696688
    std::cout << "Loading DLL at runtime...\n";
    LPCWSTR DLL_PATH = L"..\\..\\x64\\Debug\\MathDLL.dl";
    HINSTANCE hDLL = LoadLibrary(DLL_PATH);
    if (hDLL == NULL) {
        DWORD dllLoadErrorCode = GetLastError();
        std::cout << "Error: Failed to load DLL (ERROR CODE: " << dllLoadErrorCode << ")\n";
        // You can use FormatMessage to retrieve a decoded message, but it's a complex function, so... no
        return EXIT_FAILURE;
    }
    
    // NOTE: Use `dumpbin /exports ..\x64\Debug\MathDLL.dll` in Visual Studio Developer console to examine the function names in the DLL and match their name with FUNCTION_NAME
    std::cout << "Loading a function from the DLL...\n";
    LPCSTR FUNCTION_NAME = "AddInts";
    INTS_ADD_NUMBERS intsAddNumbers = (INTS_ADD_NUMBERS)GetProcAddress(hDLL, FUNCTION_NAME);
    HRESULT returnStatus = EXIT_SUCCESS;
    if (intsAddNumbers == NULL) {
        std::cout << "Error: Failed to find function \"" << FUNCTION_NAME << "\" in DLL\n";
        returnStatus = EXIT_FAILURE;
    }
    else {
        int a = 1;
        int b = 3;
        int result = intsAddNumbers(a, b);
        std::cout << "Added " << b << " to " << a << " which results in " << result << "\n";
    }
    FreeLibrary(hDLL);
    return returnStatus;
}

