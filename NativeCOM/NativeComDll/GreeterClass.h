#pragma once
#include <windows.h>
#include <unknwn.h>  // For IUnknown
#include <atomic>

// Define a unique class and interface IDs for our custom COM object
// {F5B1AC78-AF25-4B82-B93D-98F319A2A4B3}
// Generated using `uuidgen /s`, available in devloper console for visual studio
static const CLSID CLSID_Greeter = { /* 3233bc95-fb3d-4a97-aa10-a717c62f4af7 */
    0x3233bc95,
    0xfb3d,
    0x4a97,
    {0xaa, 0x10, 0xa7, 0x17, 0xc6, 0x2f, 0x4a, 0xf7}
};

static const IID IID_IGreeter = { /* d9c45dc8-9d13-4773-af01-2b9ff98dbb2a */
    0xd9c45dc8,
    0x9d13,
    0x4773,
    {0xaf, 0x01, 0x2b, 0x9f, 0xf9, 0x8d, 0xbb, 0x2a}
};

// COM interface declaration
interface __declspec(uuid("d9c45dc8-9d13-4773-af01-2b9ff98dbb2a")) IGreeter : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE Greet(LPCWSTR name) = 0;  // low level call convention is set to standard - ensures ABI compatibility, i.e. __stdcall
};

// COM implementer class
// NOTE: This uuid is CLSID_Greeter and is used when using __uuidof(Greeter)
class __declspec(uuid("3233bc95-fb3d-4a97-aa10-a717c62f4af7")) Greeter : public IGreeter {
private:
    std::atomic<ULONG> refCount = 0;
public:
    // COM Methods
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;

    // Business logic
    HRESULT STDMETHODCALLTYPE Greet(LPCWSTR name) override;

    // Constructor/Destructor
    Greeter();
    ~Greeter();
};