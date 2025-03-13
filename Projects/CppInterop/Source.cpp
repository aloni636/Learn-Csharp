#define NOMINMAX  // avoid conflic with std::numeric_limits<float>::max()
#include <iostream>
#include <bitset>
#include <sstream>  // for std::stringstream 
#include <windows.h>  // for GetConsoleScreenBufferInfo
#include <algorithm>  // for std::min & std::max
#include <array>
#include <vector>
#include <numeric>  // for recude
#include <memory>  // for smart pointers
#include <random>  // for std::mt19937
#include <map>  // for tree stuff
#include <limits>  // for casting at the limits
#include <fstream>  // for file streams
#include <stdexcept>  // for std::runtime_error
#include <regex>  // for string subsitution in log class
#include <ctime>  // for taking current time
#include <iomanip>  // for converting time to string
#include <functional>  // for function template class, used for specifying functions as parameters 
#include "MyUtilities.h"  // for messing around with compiled library (as oppose to header only lib)

template <typename T> std::string vecToString(std::vector<T> vec, std::string delimiter = ", ") {
	if (vec.size() == 0) {
		return "";
	}
	std::ostringstream oss;
	oss << "{ ";
	for (int i = 0; i < vec.size() - 1; i++) {
		oss << vec[i] << delimiter;
	}
	oss << vec.back() << " }";
	return oss.str();
}

// NOTE: not working...
std::vector<std::string> splitString(const std::string& delimitedString, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t previousPosition = 0;
    size_t currentPosition = 0;

	while (true) {
		currentPosition = delimitedString.find(delimiter, previousPosition);
		if (currentPosition == std::string::npos) break;
		std::string token = delimitedString.substr(previousPosition, currentPosition - previousPosition);
        tokens.push_back(token);
        previousPosition = currentPosition + delimiter.length();
    }
    // Push the last token (if any)
    tokens.push_back(delimitedString.substr(previousPosition));
    
    return tokens;
}

// Use templates for printing arrays vecs etc
std::string joinStrings(const std::string a, const std::string b) {
	return a + ", " + b;
}


// Maybe later...
class Node {
public:
	int data;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	bool isLeaf() const {
		return (left == nullptr) and (right == nullptr);
	};
	void populateLevelStrings(std::map<int, std::string>& levels, int currentDepth, int treeDepth) {
		//                1  
		//         3            2
		//    4         5
		//  6   7   6
		//      
		int level = treeDepth - currentDepth;
		level;
		//(*left).populateLevelStrings();
	};
	int maxTreeDepth(int currentLevel = 0) const {
		// base case
		if ((left == nullptr) and (right == nullptr)) {
			return currentLevel;
		};
		// recursive case
		int maxLevelLeft = 0, maxLevelRight = 0;
		if (left != nullptr) { maxLevelLeft = (*left).maxTreeDepth(currentLevel + 1); }
		if (right != nullptr) { maxLevelRight = (*right).maxTreeDepth(currentLevel + 1); }
		return std::max(maxLevelLeft, maxLevelRight);
	};
	/*void printNode() {
		_printNode(0);
	}*/;
};

void binaryTree() {
	// === Structs ===
	struct Node {
		int data;
		Node* left;
		Node* right;

		Node(int value) : data(value), left(nullptr), right(nullptr) {}
		~Node() {
			delete left;
			delete right;
		}
	};
	// TODO: 2. learn more about new, delete, unique_ptr and shared_ptr in a tree data structure
	std::unique_ptr<Node> root = std::make_unique<Node>(10);
	std::mt19937 rngEngine(42);  // defining rng engine
	std::uniform_int_distribution<int> randomDistribution(1, 100);  // init for config object which passes requirements to an rng engine
	int randomNumber = randomDistribution(rngEngine);  // passing config to rng engine
	/*for (int i = 1; i < 12; i++) {
		root
	}*/
}

void dataStructures() {
	// int, floats, doubles, bools, string
	// convention is camelCase for funcs and variables 
	int integer = 1;
	float floatingNumber = 1.1f;
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

	size_t streamLength = streamString.length();
	std::cout << streamString;
	std::cout << "\n^" << std::string(
		std::max<std::size_t>(0, streamString.length() - std::to_string(streamLength).length() - 3),
		'-'
	) << " " << std::to_string(streamLength) << "\n";

	const std::string DELIMITER = "| ";
	std::cout << "I can split strings by \"" + DELIMITER + "\" delimiter:\n";
	std::string userInputString;
	std::getline(std::cin, userInputString);
	auto stringTokens = splitString(userInputString, DELIMITER);
	std::cout << vecToString(stringTokens)  << "\n";
	// TODO: 8. (DONE) split by delimiter using std::getline, and store in composite vec
	// std::string word 

	// composites: arrays, vectors, structs
	// === Arrays ===
	std::array<int, 5> intArray = { 1,2,3,4,5 };
	std::stringstream intArrayStream;
	intArrayStream << "Array of ints: { ";
	for (int num : intArray) { intArrayStream << num << ", "; };
	intArrayStream << "}\n";
	std::cout << intArrayStream.str();

	// === Vectors ===
	std::vector<std::string> stringVec = { "One is", "Two but", "Four is one?!" };
	std::cout << "\nstringVec: {" << std::accumulate(stringVec.begin(), stringVec.end(), stringVec[0], joinStrings) << "}";
	std::cout << "\nstringVec (again): {" << std::accumulate(
		stringVec.begin(),
		stringVec.end(),
		stringVec[0],
		[](std::string a, std::string b) {return a + ", " + b;}  // lambda function
	) << "}";


	// === structs ===
	struct CreditCard {
		int useCount;
		int cardNumber;
		// add overloaded printing << 
	};

	struct Person {
		std::string name;
		CreditCard* card;
	};


	// TODO: 10. print hex representation
	std::cout << "\ninteger: " << integer << " hex: " << std::hex << integer << std::dec;
	// TODO: 9. make hex repr make sense
	std::cout << "\nfloating number: " << floatingNumber << " hex: " << std::hex << *reinterpret_cast<unsigned int*>(&floatingNumber) << std::dec;
	std::cout << "\ndouble precision number: " << doublePrecisionNumber << " hex: " << std::hex << *reinterpret_cast<unsigned int*>(&doublePrecisionNumber) << std::dec;
	std::cout << "\n";
	
	// TODO: 3. (DONE) learn about static_cast & reinterpret_cast
	// Type safe casting using `static_cast`
	float int32MaxAsFloat = static_cast<float>(INT32_MAX);
	std::cout << "I made max int32 as float: " << int32MaxAsFloat << "\n";
	float maxFloat32 = std::numeric_limits<float>::max();
	double maxFloat32AsDouble = static_cast<double>(maxFloat32);
	std::cout << "I made max float32 as double: " << maxFloat32AsDouble << "\n";
	
	char32_t unicodeCharacter = '🤩';
	int32_t unicodeCharacterAsInt32 = static_cast<int32_t>(unicodeCharacter);
	std::cout << "I made unicode as int32: " << unicodeCharacterAsInt32 << "\n";

	// Unsafe casting
	// std::string unicodeString = "🤩";
	// int32_t* unicodeStringAsInt32Pointer = reinterpret_cast<int32_t*>(unicodeString);
	float floatingPointNumber = 3.1415f;

	// Reinterpret the float's bits as an unsigned int
	unsigned int floatBits = *reinterpret_cast<unsigned int*>(&floatingPointNumber);
	std::cout << "Float: " << floatingPointNumber << " Hex: 0x" << std::hex << floatBits << std::dec << "\n";

	// Reinterpret as void pointer
	void* floatingPointNumberAsVoidPointer = reinterpret_cast<void*>(&floatingPointNumber);
	std::cout << "Floating point number as void pointer casted to int pointer: " << *reinterpret_cast<int32_t*>(floatingPointNumberAsVoidPointer) << "\n";
}

//void printSeparator() {
//
//}

void pointers() {
	// === refs ===
	std::string pizza = "🍕";
	std::string& samePizza = pizza;
	std::string pizzaCopy = pizza;
	// #pragma warning(suppress: 4305 4309)
	// occurred because '⌚' is a multi byte unicode, but got truncated to fit into a byte which overrides the first byte of the pizza
	pizza.at(0) = '\xFF';
	std::cout << "original pizza: " << pizza << "\n";
	std::cout << "pizza reference: " << samePizza << "\n";
	std::cout << "pizza copy: " << pizzaCopy << "\n";
	
	std::cout << "pizza address: " << &pizzaCopy << "\n";
	
	std::string* pizzaPointer = &pizza;
	std::cout << "pizza pointer: " << pizzaPointer << "\n";
	std::cout << "pizza dereference: " << *pizzaPointer << "\n";
	*pizzaPointer = "🍕";
	std::cout << "pizza dereference after making it pizza again: " << *pizzaPointer << "\n";

	// TODO 1. (DONE): RAII unique_ptr & shared_ptr
	std::unique_ptr<std::string> pizzaUniquePointer = std::make_unique<std::string>(pizza);
	std::cout << "pizza unique pointer dereference: " << *pizzaUniquePointer << "\n";
	*pizzaUniquePointer = "🚤";
	std::cout << "pizza unique pointer dereference after conversion to boat: " << *pizzaUniquePointer << "\n";
	
	// RAII: no valid conversion from string unique_ptr to regular string ptr
	// In this case, RAII is enforced at the type level
	// std::string* anotherPizzaPointer = pizzaUniquePointer;
	// RAII: unique_ptr is a deleted function, which is RAII enforced at compile time (I think...)
	// std::unique_ptr<std::string> anotherPizzaUniquePointer = pizzaUniquePointer;
	std::unique_ptr<std::string> anotherPizzaUniquePointer = std::move(pizzaUniquePointer);
	//std::cout << "pizzaUniquePointer after std::move: " << pizzaUniquePointer << "\n";  // 
	//std::cout << "dereferencing pizzaUniquePointer after std::move: " << *pizzaUniquePointer << "\n";  // crash
	std::shared_ptr<std::string> sharedPizzaUniquePointer = std::make_shared<std::string>(pizza);
	std::shared_ptr<std::string> anotherSharedPizzaUniquePointer = sharedPizzaUniquePointer;  // this works
	std::cout << "pizza shared pointer dereference (1): " << *sharedPizzaUniquePointer << "\n";
	std::cout << "pizza shared pointer dereference (2): " << *anotherSharedPizzaUniquePointer << "\n";
	std::cout << "shared pizza pointers count (1): " << sharedPizzaUniquePointer.use_count() << "\n";
	std::cout << "shared pizza pointers count (2): " << anotherSharedPizzaUniquePointer.use_count() << "\n";
	std::cout << "buckle your seatbelts, boys, were entering a local scope!\n";
	{
		std::shared_ptr<std::string> localSharedPizzaUniquePointer = sharedPizzaUniquePointer;
		std::cout << "shared pizza pointers count (1): " << sharedPizzaUniquePointer.use_count() << "\n";
	}
	std::cout << "relax, boys! we've existed local scope!\n";
	std::cout << "shared pizza pointers count after exiting local scope (1): " << sharedPizzaUniquePointer.use_count() << "\n";
}

// cannot be declared inside a function...
// optional params
void printMulti(std::string source, int count) {
	for (int i = 0; i < count; i++) {
		std::cout << source << "\n";
	};
};
void printMulti(std::string source) { printMulti(source, 1); };

// TODO: 7. Recursive triangle print

// TODO: 4. (DONE) Classes (constructors, destructors, member functions)

class RandomLinePicker {
private:
	std::string csvPath;
	std::mt19937 rngEngine;
	std::uniform_int_distribution<int> csvRandomDistribution;  // init for config object which passes requirements to an rng engine
	std::vector<std::string> lines;

public:
	RandomLinePicker(std::string csvPath) {
		std::random_device rd;
		*this = RandomLinePicker(csvPath, rd());
	}

	RandomLinePicker(std::string csvPath, int seed) {
		std::ifstream file(csvPath);
		if (!file.is_open()) {
			throw std::runtime_error("cannot open file: " + csvPath);
		}
		std::string line;
		while (std::getline(file, line, '\n')) {
			lines.push_back(line);
		}
		rngEngine = std::mt19937(seed);
		csvRandomDistribution = std::uniform_int_distribution<int>(0, static_cast<int>(lines.size() - 1));
	}
	std::string pickOne() {
		int randomIndex = csvRandomDistribution(rngEngine);
		return lines[randomIndex];
	}
	std::vector < std::string> pickMany(int count) {
		std::vector<std::string> out(count);
		for (int i = 0; i < count; i++) {
			int randomIndex = csvRandomDistribution(rngEngine);
			out[i] = lines[randomIndex];
		}
		return out;
	}
};



void classes() {
	RandomLinePicker linePicker = RandomLinePicker("./words.csv");
	std::cout << "random word from csv: " << linePicker.pickOne() << "\n";
	std::cout << "random word from csv: " << vecToString(linePicker.pickMany(5)) << "\n";

}
// TODO: 5. (DONE) Inheritance, virtual functions, and polymorphism

class AbstractLogger {
protected:
	std::string format = "{time} {message}";
	std::string formatMessage(std::string message) {
		std::string outMessage = format;  // copy
		std::time_t currentTime = std::time(nullptr);
		std::tm localTime;
		::localtime_s(&localTime, &currentTime);  // extrernal C library, not in std
		
		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		std::string localTimeString = oss.str();

		outMessage = std::regex_replace(outMessage, std::regex(R"(\{time\})"), localTimeString);
		outMessage = std::regex_replace(outMessage, std::regex(R"(\{message\})"), message);
		return outMessage;
	}
public:
	virtual void log(std::string message) = 0;  // pure virtual function, i.e. abstract method
	virtual void logMultiple(std::vector<std::string> messages) {
		for (std::string message : messages) {
			log(message);
		}
	};
	void setFormat(const std::string newFormat) {
		format = newFormat;
	}
	virtual ~AbstractLogger() = default;
};


class ConsoleLogger : public AbstractLogger {  // `public` is used because default behavior is private, which means I cannot access any virtual method
public:
	void log(std::string message) override {  // override must not be omitted to prevent the compiler to treat this as overloading with different signature
		std::cout << formatMessage(message);
	}
};


class FileLogger : public AbstractLogger {
private:
	std::string filePath;
public:
	FileLogger(std::string logPath) : filePath(logPath) {
		filePath = logPath;
	}

	void log(std::string message) override {
		std::ofstream file(filePath, std::ios::app);  // append mode
		if (!file.is_open()) {
			throw std::runtime_error("couldn't open log file at " + filePath);
		};
		file << formatMessage(message) << "\n";
		file.close();
	};
	void logMultiple(std::vector<std::string> messages) {
		std::ofstream file(filePath);
		if (!file.is_open()) {
			throw std::runtime_error("couldn't open log file at " + filePath);
		};
		for (std::string message : messages) {
			file << formatMessage(message) << "\n";
		}
		file.close();
	}
};
void inheritance() {
	ConsoleLogger consoleLogger{};  // {} Uniform Initialization, resolves ambiguity with function definition
	FileLogger fileLogger{ "./cpp_log.txt" };
	consoleLogger.log("hello world from logger!");
	fileLogger.log("I was just written to the file system!");
}

// TODO: 6.   (DONE) Function templates
// TODO: 6.1. Class templates
// TODO: 6.2. Function templates INSIDE class templates
// TODO: 6.3. (DONE) Variadic function templates
// TODO: 6.4. (DONE) Function template specialization
// TODO: 7. <type_traits>
// TODO: 8. (partially done) Fold expressions
void templates() {
	
	std::cout << "vecToString in int vec: " << vecToString(std::vector<int>({1,2,3,4,5})) << "\n";
}

void functions() {
	std::cout << "\nprintMulti(\"hello\", 2):\n";
	printMulti("hello", 2);
	std::cout << "printMulti(\"hello\"):\n";
	printMulti("hello");
}
void controlStructures() {}  // including exceptions

void preprocessorDirectives() {}  // make cross platfrom getTerminalWidth

void includes() {
	int foreignAddition = addNumbers(1, 2);
	std::cout << "Computing 1+2 using compiled lib:" << foreignAddition << "\n";

	const char* a = "hello";
	const char* b = "world";
	std::string ab = concatenateStrings(a, b);
	std::cout << "Concatenating 2 c style strings using compiled lib:" << foreignAddition;
}

// +---------------------------------------------------------------------------------------------+
// | Expression Side       | Formal Name                    | Example                            |
// |-----------------------|--------------------------------|------------------------------------|
// | Left side (= target)  | Lvalue (Assignable Expression) | x = 5; (x is the lvalue)           |
// | Right side (= source) | Rvalue (Evaluated Expression)  | x = y + 10; (y + 10 is the rvalue) |
// +---------------------------------------------------------------------------------------------+
template <typename... Functions>
void invokeWithSeparator(char separator, Functions&&... functions) {  // && is universal ref, capabale of holding both lvalue (assignemnt target) and rvalue objects (assignment source, like lambdas)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	
	((functions(), std::cout << "\n\n" << std::string(consoleWidth, separator) << "\n\n"), ...);  // requires cpp17
}

template <typename... Functions>
void invokeWithSeparator(Functions&&... functions) {
	invokeWithSeparator('-', functions...);
}

int main(int argc, char** argv) {
	SetConsoleOutputCP(CP_UTF8);
	invokeWithSeparator(
		'*',
		dataStructures,
		pointers,
		functions,
		classes,
		inheritance,
		templates,
		includes
	);
	return 0;
}