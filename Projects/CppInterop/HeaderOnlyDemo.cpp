#include "HeaderOnlyLib.h"  // My first header only lib!
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>  // for std::stringstream 

template <typename K, typename V>
std::string reprMap(std::map<K, V> map) {
	std::stringstream stringStream;
	stringStream << "{";

	for (auto const& t : map) {
		K key = t.first;
		V value = t.second;
		stringStream << key << " => " << value << ", ";
	}
	stringStream << "}";
	return stringStream.str();
}

int main(int argc, char** argv) {
	//Histogram histogramGenerator(5);
	std::vector<int> vec = { 1,2,3,4,5 };
	std::map<double, int> histogram = computeHistogram<int>(vec, 2);
	//std::map<int, int> histogramMap = histogramGenerator.compute(vec);
	std::cout << "Histogram: " << reprMap(histogram);
}