#include <string>
#include <map>
#include <vector>
#include <stdexcept>
// TODO 1: simple function w/overloading
// TODO 2: simple class

int addNumbers(int a, int b) { return a + b; };
float addNumbers(float a, float b) { return a + b; };

std::string concatenateStrings(std::string& a, std::string& b) { return a + b; };
std::string concatenateStrings(const char* a, const char* b) {
	if (a == nullptr or b == nullptr) {
		throw std::runtime_error("Cannot convert ");
	};
	return std::string(a) + std::string(b);

};