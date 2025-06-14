#import "libid:f5eb3f19-113a-4265-93d5-83cab932c7b5" \
        named_guids \
        raw_interfaces_only \
        no_namespace

#include <atlbase.h>
#include <atlcomcli.h>
#include <iostream>

int wmain()
{
    std::cout << "[C/C++]: Starting COM session\n";
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) { std::cout << "COM init failed\n"; return 1; }

    ATL::CComPtr<IGreeter> spGreeter;
    hr = spGreeter.CoCreateInstance(CLSID_Greeter);
    if (SUCCEEDED(hr))
    {
        ATL::CComBSTR name(L"Elyasaf");
        spGreeter->Greet(name);
    }
    else
    {
        std::cout << "CoCreateInstance failed 0x" << std::hex << hr << '\n';
    }

    CoUninitialize();
    std::cout << "[C/C++]: Closing COM session\n";
    return 0;
}