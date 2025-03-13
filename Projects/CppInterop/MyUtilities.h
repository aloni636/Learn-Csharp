#pragma once  // disallowing multiple inclusion when compiling, avoiding duplicate definition of methods and preventing compilation errors
#include <string>
#include <map>
#include <vector>

// TODO 1 (DONE): simple function w/overloading
// TODO 2: simple class

int addNumbers(int a, int b);
float addNumbers(float a, float b);

std::string concatenateStrings(std::string& a, std::string& b);
std::string concatenateStrings(const char* a, const char* b);


// NOTE: Templates cannot be separated into declaration and implementation
//class Histogram {
//public:
//	Histogram(int bins) {};
//	std::map<double, int> compute(std::vector<>) {};
//};
