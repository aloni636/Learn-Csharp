// #include <windows.h>
#include <unknwn.h>
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FAKECOMDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FAKECOMDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FAKECOMDLL_EXPORTS
#define FAKECOMDLL_API __declspec(dllexport)
#else
#define FAKECOMDLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
// class FAKECOMDLL_API CFakeComDLL {
// public:
// 	CFakeComDLL(void);
// 	// TODO: add your methods here.
// };

// extern FAKECOMDLL_API int nFakeComDLL;

FAKECOMDLL_API IUnknown* GetFakeFactory(void);
