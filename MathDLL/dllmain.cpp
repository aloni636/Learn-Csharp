// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        std::cout << "[C++/DLL]: DLL_PROCESS_ATTACH event triggered!\n";
    }
    case DLL_THREAD_ATTACH:{
        std::cout << "[C++/DLL]: DLL_THREAD_ATTACH event triggered!\n";
    }
    case DLL_THREAD_DETACH: {
        std::cout << "[C++/DLL]: DLL_THREAD_DETACH event triggered!\n";
    }
    case DLL_PROCESS_DETACH: {
        std::cout << "[C++/DLL]: DLL_PROCESS_DETACH event triggered!\n";
    }
        break;
    }
    return TRUE;
}

