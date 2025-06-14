// Greeter.cpp : Implementation of CGreeter

#include "pch.h"
#include "Greeter.h"
#include <iostream>

// CGreeter


STDMETHODIMP CGreeter::Greet(BSTR name)
{
    // TODO: Add your implementation code here
    std::wcout << L"[ATL]: Greeting, " << name << L"!\n";
    return S_OK;
}
