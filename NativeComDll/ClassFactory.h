#pragma once
#include <windows.h>
#include <atomic>
#include <sal.h>

#ifdef NATIVECOMDLL_EXPORTS  // preprocessor macro defined by default in a DLL visual studio C++ project
#define NATIVECOMDLL_API __declspec(dllexport)
#else
#define NATIVECOMDLL_API __declspec(dllimport)
#endif

// Factory that creates Greeter instances
class GreeterClassFactory : public IClassFactory {
private:
    std::atomic<ULONG> refCount = 0;
public:
    // Constructor / Destructor
    GreeterClassFactory();
    ~GreeterClassFactory();

    // IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;

    // IClassFactory
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override;
    HRESULT STDMETHODCALLTYPE LockServer(BOOL) override;
};

// +---------------------------------------------------------------------------------------------------------------------------- +
// | Function            | In your DLL ?                | When it’s used                                                         |
// | DllGetClassObject   | Yes                          | COM calls this to get your factory when someone calls CoCreateInstance |
// | DllCanUnloadNow     | Yes                          | COM calls this to decide whether your DLL can be unloaded              |
// | DllRegisterServer   | Optional but recommended     | regsvr32 calls this to write CLSIDs into registry                      |
// | DllUnregisterServer | Optional                     | regsvr32 / u calls this to clean up                                    |
// | CoInitialize        | In the client                | Called by the client before any COM calls                              |
// | CoCreateInstance    | In the client                | Used to request an object from your DLL                                |
// +---------------------------------------------------------------------------------------------------------------------------- +

// Exported function for CoCreateInstance
// NOTE: Windows already declares those functions in combaseapi.h
// combaseapi.h
// extern "C" NATIVECOMDLL_API HRESULT STDMETHODCALLTYPE DllGetClassObject(_In_ REFCLSID clsid, _In_ REFIID riid, _Out_ LPVOID* ppv);
// 
// DLL lifetime functions 
// combaseapi.h
// extern "C" NATIVECOMDLL_API HRESULT STDMETHODCALLTYPE DllCanUnloadNow();  // Tracks managed objects lifetimes to signal when the DLL is no longer necessary
// olectl.h
// extern "C" NATIVECOMDLL_API HRESULT STDMETHODCALLTYPE DllRegisterServer();  // Registration of COM server registry keys
// olectl.h
// extern "C" NATIVECOMDLL_API HRESULT STDMETHODCALLTYPE DllUnregisterServer();  // Deletion of COM server registry keys
