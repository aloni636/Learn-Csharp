#include <iostream>
#include <bitset>
#include <sstream>  // for std::stringstream 
#include <windows.h>  // for GetConsoleScreenBufferInfo
#include <algorithm>  // for std::min & std::max

void dataStructures() {
	// int, floats, doubles, bools, string
	// convention is camelCase for funcs and variables 
	int integer = 1;
	float floatingNumber = 1.1;
	double doublePrecisionNumber = 1.2455;
	bool flag;
	flag = integer == 5;
	std::string stringVariable = "hello world";
	char C = 'C', p = '+';
	std::string cpp;
	cpp = cpp + C + p + p;

	std::stringstream stream;
	stream << stringVariable << " from " << cpp << "!";

	std::string streamString = stream.str();

	int streamLength = streamString.length();
	std::cout << streamString;
	std::cout << "\n^" << std::string(
		std::max<std::size_t>(0, streamString.length() - std::to_string(streamLength).length() - 3),
		'-'
	) << " " << std::to_string(streamLength) << "\n";

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	std::cout << "\n" << std::string(consoleWidth, '-') << "\n";
	// composites: arrays, vectors, structs
	
	// TODO: print hex representation
	std::cout << "\ninteger: " << integer << " hex: " << std::hex << integer << std::dec;
	// TODO: make hex repr make sense
	std::cout << "\nfloating number: " << floatingNumber << " hex: " << std::hex << *reinterpret_cast<unsigned int*>(&floatingNumber) << std::dec;
	std::cout << "\ndouble precision number: " << doublePrecisionNumber << " hex: " << std::hex << *reinterpret_cast<unsigned int*>(&doublePrecisionNumber) << std::dec;
	std::cout << "\n";

	
}

//void printSeparator() {
//
//}

void pointers() {}

void controlStructures() {}

void preprocessorDirectives() {}  // make cross platfrom getTerminalWidth

int main(int argc, char** argv) {
	dataStructures();
	return 0;
}