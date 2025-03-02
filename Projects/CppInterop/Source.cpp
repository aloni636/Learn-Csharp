#include <iostream>

void data_structures() {
	int integer = 1;
	float floating_number = 1.1;
	double double_precision_number = 1.2455;
	//std:: floating_number  // TODO: print hex representation
	std::cout << "Hello world from C++!"
		<< "\ninteger: " << integer << " hex: " << std::hex << integer;
	std::cout << "\nfloating number: " << floating_number << " hex: " << std::hexfloat << floating_number;
	std::cout << "\ndouble precision number: " << double_precision_number << " hex: " << std::hexfloat << double_precision_number;
	std::cout << "\n";
}

void control_structures() {

}

int main(int argc, char** argv) {
	data_structures();
	return 0;
}