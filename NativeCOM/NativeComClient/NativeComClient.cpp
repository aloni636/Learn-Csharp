#include <iostream>
#include <windows.h>
#include <atlbase.h>  // RAII COM memory management
#include "GreeterClass.h"  // NOTE: To include from another project use additional include directories in Project -> Properties -> C/C++ -> General -> Additional Include Directories: ../NativeComDll

int main()
{
    HRESULT hr;
    std::cout << "[C/C++]: Starting COM session\n";
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    // Scoping all COM operations between CoInitializeEx and CoUninitialize guarantees RAII deallocations (i.e. CComPtr<IGreeter>) BEFORE releasiing the core COM libraries
    {
        if (FAILED(hr)) { return EXIT_FAILURE; }
        IGreeter* pGreeter = nullptr;
        hr = CoCreateInstance(CLSID_Greeter, nullptr, CLSCTX_INPROC_SERVER, IID_IGreeter, (void**)&pGreeter);
        if (FAILED(hr)) {
            std::cout << "[C]: Failed to create instance of Greeter.\n";
            return EXIT_FAILURE;
        }
        pGreeter->Greet(L"Elyasaf");
        pGreeter->Release();

        CComPtr<IGreeter> spGreeter;
        hr = spGreeter.CoCreateInstance(__uuidof(Greeter));
        if (FAILED(hr)) {
            std::cout << "[C++]: Failed to create instance of Greeter.\n";
            return EXIT_FAILURE;
        }
        spGreeter->Greet(L"Elyasaf");
    }
    CoUninitialize();
    std::cout << "[C/C++]: Closing COM session\n";
}
