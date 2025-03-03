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

// NOTE: not working...
std::vector<std::string> splitString(const std::string& delimitedString, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t previousPosition = 0;
    size_t currentPosition = 0;

    while ((currentPosition = delimitedString.find(delimiter, previousPosition)) != std::string::npos) {
        tokens.push_back(delimitedString.substr(previousPosition, currentPosition - previousPosition));
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
	// TODO: 2. learn more about new, delete, unique_ptr and shared_ptr
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

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	std::cout << "\n" << std::string(consoleWidth, '-') << "\n";

	std::cout << "I can split strings by '|' delimiter:\n";
	std::string inputDelimitedString;
	std::cin >> inputDelimitedString;
	auto stringTokens = splitString(inputDelimitedString, "|");
	for (std::string token : stringTokens) { std::cout << token << ", "; };  // for each loop
	std::cout << "\n";
	// TODO: 8. split by delimiter using std::getline, and store in composite vec
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
	// TODO: 3. learn about static_cast & reinterpret_cast

	
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
	std::cout << "pizza derefrence: " << *pizzaPointer << "\n";
	*pizzaPointer = "🍕";
	std::cout << "pizza derefrence after making it pizza again: " << *pizzaPointer << "\n";

	// TODO: 1. RAII unique_ptr & shared_ptr
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

// TODO: 4. Classes (constructors, destructors, member functions)

// TODO: 5. Inheritance, virtual functions, and polymorphism

// TODO: 6. Templates

void functions() {
	std::cout << "\nprintMulti(\"hello\", 2):\n";
	printMulti("hello", 2);
	std::cout << "printMulti(\"hello\"):\n";
	printMulti("hello");
}
void controlStructures() {}  // including exceptions

void preprocessorDirectives() {}  // make cross platfrom getTerminalWidth

int main(int argc, char** argv) {
	SetConsoleOutputCP(CP_UTF8);
	dataStructures();
	pointers();
	functions();
	return 0;
}