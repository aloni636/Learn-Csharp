#include "pch.h"
#include "MyComObject.h"
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

ULONG Greeter::AddRef() { return ++refCount; };

ULONG Greeter::Release() { 
    ULONG count = --refCount;  // storing in new variable to successfully return after delete
    if (count == 0) {
        dllReferences--;
        delete this;
    }
    return count;
};

// Business Logic
HRESULT Greeter::Greet(PWSTR name) {
    std::wcout << L"Greeting, " << name << L"!";
    return S_OK;
};

