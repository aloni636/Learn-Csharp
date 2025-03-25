#include "pch.h"  // Ref: https://stackoverflow.com/a/54122035
#include "MathLib.h"
#include <iostream>

int MathLib::AddNumbers(int a, int b) {
	std::cout << "[C++/DLL]: Adding (int) " << b << " to " << a << "\n";
	return a + b;
}

int MathLib::AddNumbers(float a, float b) {
	std::cout << "[C++/DLL]: Adding (float) " << b << " to " << a << "\n";
	return static_cast<int>(a + b);
}

int MathLib::AddNumbers(double a, double b) {
	std::cout << "[C++/DLL]: Adding (double) " << b << " to " << a << "\n";
	return static_cast<int>(a + b);
}