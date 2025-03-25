#pragma once

#ifdef MATHDLL_EXPORTS  // preprocessor macro defined by default in a DLL visual studio C++ project
#define MATHDLL_API __declspec(dllexport)  // __declspec(dllexport) (meaning declaration specifier) is used in the header file to declare that a function should be visible to the DLL consumer
#else
#define MATHDLL_API __declspec(dllimport)  // Used when built against a consumer (as MATHDLL_EXPORTS is no defined) when implicitly loading the DLL; Ref: https://learn.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll?view=msvc-170#:~:text=data%20exported%20by%20the%20DLL%20must%20all%20be%20marked%20__declspec(dllimport)%20in%20the%20header%20file
#endif
//
namespace MathLib {
	// `extern "c"` is not used here because the DLL consumers are going to use C++
	MATHDLL_API int AddNumbers(int a, int b);

	MATHDLL_API int AddNumbers(float a, float b);

	MATHDLL_API int AddNumbers(double a, double b);
}

 extern "C" MATHDLL_API int AddInts(int a, int b);