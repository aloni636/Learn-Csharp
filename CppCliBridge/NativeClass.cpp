#include "pch.h"
#include "NativeClass.h"

// the :: syntax is because we are overriding the decleration with implementation, i.e. we imported the class in the header file and now populate the empty signatures with implementation code
RandomNumberGenerator::RandomNumberGenerator(int seed, int min, int max) {
	this->min = min;
	this->max = max;
	this->seed = seed;
	this->rngEngine = std::mt19937(seed);
	this->randomDistribution = std::uniform_int_distribution<int>(min, max);
}
RandomNumberGenerator::RandomNumberGenerator(int min, int max) {
	std::random_device rd;
	RandomNumberGenerator(rd(), min, max);
}
int RandomNumberGenerator::generate() {
	return this->randomDistribution(this->rngEngine);
}
