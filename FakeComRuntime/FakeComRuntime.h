// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FAKECOMRUNTIME_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FAKECOMRUNTIME_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FAKECOMRUNTIME_EXPORTS
#define FAKECOMRUNTIME_API __declspec(dllexport)
#else
#define FAKECOMRUNTIME_API __declspec(dllimport)
#endif

// This class is exported from the dll
class FAKECOMRUNTIME_API CFakeComRuntime {
public:
	CFakeComRuntime(void);
	// TODO: add your methods here.
};

extern FAKECOMRUNTIME_API int nFakeComRuntime;

FAKECOMRUNTIME_API int fnFakeComRuntime(void);
