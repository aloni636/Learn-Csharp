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
#include <limits>

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
    constexpr float maxFloat32 = std::numeric_limits<float>::max();
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