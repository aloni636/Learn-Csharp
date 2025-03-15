#pragma once
#include <string>
#include <random>

class RandomNumberGenerator {
private:
	int seed;
	int min;
	int max;
	std::mt19937 rngEngine;
	std::uniform_int_distribution<int> randomDistribution;
public:
	RandomNumberGenerator(int seed, int min, int max);
	RandomNumberGenerator(int min, int max);
	int generate();
};