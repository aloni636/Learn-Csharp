#include "pch.h"
#include "GreeterClass.h"
#include <iostream>
#include "Globals.h"

// The COM object that implements IGreeter
Greeter::Greeter() {};
Greeter::~Greeter() {};

// IUnknown Methods
HRESULT Greeter::QueryInterface(REFIID riid, void** ppvObject) {
    if (ppvObject == nullptr) { return E_POINTER; }  // Ref: https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-queryinterface(refiid_void)

    if (riid == IID_IGreeter) {
        *ppvObject = static_cast<IGreeter*>(this);
    }
    // Handle every riid possible using static_cast
    else if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknown*>(this);
    } 
    else {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    this->AddRef();  // NOTE: `this` is a pointer (`->`) to the class instance, not an object (`.`)
    return S_OK;
};

ULONG Greeter::AddRef() { 
    std::cout << "[COM]: Incrementing reference count of Greeter (" << this << "): " << this->refCount+1 << " refs\n";
    return ++refCount; 
};

ULONG Greeter::Release() { 
    ULONG count = --refCount;  // storing in new variable to successfully return after delete
    std::cout << "[COM]: Decrementing reference count of Greeter (" << this << "): " << count << " refs\n";
    if (count == 0) {
        dllReferences--;
        std::cout << "[COM]: Deleting Greeter (" << this << ").\n";
        delete this;
    }
    return count;
};

// Business Logic
HRESULT Greeter::Greet(LPCWSTR name) {
    std::wcout << L"Greeting, " << name << L"!\n";
    return S_OK;
};

