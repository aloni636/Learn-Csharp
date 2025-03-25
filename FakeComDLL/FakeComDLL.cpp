// FakeComDLL.cpp : Defines the exported functions for the DLL.

#include "pch.h"
#include "framework.h"
#include "FakeComDLL.h"
#include <atomic>

// This is an example of an exported variable
// FAKECOMDLL_API int nFakeComDLL=0;

class FakeFactory : public IClassFactory {
private:
    std::atomic<ULONG> references = 1;
public:
    FakeFactory() {};
    ~FakeFactory() {};
    
    HRESULT CreateInstance(
        // NOTE: It appears like the square bracket thing before type definition is a valid C++ syntax
        [in]  IUnknown* pUnkOuter,
        [in]  REFIID   riid,
        [out] void** ppvObject
    ) {
        if (pUnkOuter != NULL) { return CLASS_E_NOAGGREGATION;  }
        if (riid !=)
    };
    HRESULT LockServer(BOOL fLock){
        return E_FAIL;  // ~~NOTE: Should actually be with accordance to offical COM conventions~~
    }
    ULONG AddRef() override {
        return ++references;
    }
    ULONG Release() override {
        ULONG refs = --references;
        if (refs == 0) {
            delete this;
        }
        return refs;
    }
};

// This is an example of an exported function.
FAKECOMDLL_API IUnknown* GetFakeFactory(void)
{
    FakeFactory* factory = new FakeFactory();
    return static_cast<IUnknown*>(factory);
}

// This is the constructor of a class that has been exported.
// CFakeComDLL::CFakeComDLL()
// {
//     return;
// }
