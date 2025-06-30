/* #import allows to include header files from registered objects by using their interface id

*/
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

    // Greeter class
    ATL::CComPtr<IGreeter> spGreeter;
    hr = spGreeter.CoCreateInstance(CLSID_Greeter);
    if (SUCCEEDED(hr))
    {
        ATL::CComBSTR name(L"Elyasaf");
        spGreeter->Greet(name);
    }
    else
    {
        std::cout << "CoCreateInstance failed for Greater class: 0x" << std::hex << hr << '\n';
    }

    // lambda block to allow early escaping while still executing a cleanup code section
    // kinda like exception's finally...
    [&]() {
        // StringGenerator class
        ATL::CComPtr<IEnumString> spGen;
        hr = spGen.CoCreateInstance(CLSID_StringGenerator);
        if (FAILED(hr)) {
            std::cout << "CoCreateInstance failed for StringGenerator class: 0x" << std::hex << hr << '\n';
            return;
        }

        // Next() method
        LPOLESTR results[2] = { nullptr };
        ULONG fetched = 0;
        hr = spGen->Next(2, results, &fetched);
        std::wcout << L"Next(2): fetched=" << fetched << L", hr=0x" << std::hex << hr << L"\n";
        for (ULONG i = 0; i < fetched; ++i) {
            std::wcout << L"  [" << i << L"] = " << results[i] << L"\n";
            CoTaskMemFree(results[i]);  // must free each string
        }

        // Clone method
        CComPtr<IEnumString> spGenClone;
        hr = spGen->Clone(&spGenClone);
        if (FAILED(hr)) {
            std::cout << "spGen->Clone failed: 0x" << std::hex << hr << '\n';
            return;
        }
        std::wcout << L"Clone(): hr=0x" << std::hex << hr << L"\n";

        // pull one string from original and clone to compare their state
        LPOLESTR one = nullptr;
        ULONG got = 0;
        hr = spGen->Next(1, &one, &got);
        if (got == 1) {
            std::wcout << L"   Next(1) for spGen = " << one << L"\n";
            CoTaskMemFree(one);
        }
        hr = spGenClone->Next(1, &one, &got);
        if (got == 1) {
            std::wcout << L"   Next(1) for spGenClone = " << one << L"\n";
            CoTaskMemFree(one);
        }

        // Skip method
        hr = spGen->Skip(1);
        std::wcout << L"Skip(1): hr=0x" << std::hex << hr << L"\n";
        hr = spGen->Next(1, &one, &got);
        if (got == 1) {
            std::wcout << L"   Next(1) for spGen after Skip(1) = " << one << L"\n";
            CoTaskMemFree(one);
        }
        hr = spGenClone->Next(1, &one, &got);
        if (got == 1) {
            std::wcout << L"   Next(1) for spGenClone = " << one << L"\n";
            CoTaskMemFree(one);
        }

        // Reset method
        hr = spGen->Reset();
        std::wcout << L"Reset(): hr=0x" << std::hex << hr << L"\n";
        hr = spGen->Next(1, &one, &got);
        if (got == 1) {
            std::wcout << L"   Next(1) for spGen after Reset() = " << one << L"\n";
            CoTaskMemFree(one);
        }
        hr = spGenClone->Next(1, &one, &got);
        if (got == 1) {
            std::wcout << L"   Next(1) for spGenClone = " << one << L"\n";
            CoTaskMemFree(one);
        }
        }();



    CoUninitialize();
    std::cout << "[C/C++]: Closing COM session\n";
    return 0;
}