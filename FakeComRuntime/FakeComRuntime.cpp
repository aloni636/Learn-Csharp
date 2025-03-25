// FakeComRuntime.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "FakeComRuntime.h"


// This is an example of an exported variable
FAKECOMRUNTIME_API int nFakeComRuntime=0;

// This is an example of an exported function.
FAKECOMRUNTIME_API int fnFakeComRuntime(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CFakeComRuntime::CFakeComRuntime()
{
    return;
}
