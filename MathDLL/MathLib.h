#pragma once

#ifdef MATHDLL_EXPORTS  // preprocessor macro defined by default in a DLL visual studio C++ project
#define MATHDLL_API __declspec(dllexport)  // __declspec(dllexport) (meaning declaration specifier) is used in the header file to declare that a function should be visible to the DLL consumer
#else
#define MATHDLL_API __declspec(dllimport)
#endif

namespace MathLib {
	// `extern "c"` is not used here because the DLL consumers are going to use C++
	MATHDLL_API int AddNumbers(int a, int b);

	MATHDLL_API int AddNumbers(float a, float b);

	MATHDLL_API int AddNumbers(double a, double b);
}