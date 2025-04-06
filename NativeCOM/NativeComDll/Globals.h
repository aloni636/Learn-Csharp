#pragma once
#include <windows.h>
#include <atomic>

// Global variables
extern std::atomic<ULONG> dllReferences;  // Used to keep track of DLL managed objects and mark when the DLL is no longer used