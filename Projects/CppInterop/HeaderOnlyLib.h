#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

// TODO: Convert to function

// NOTE: Templates cannot be separated into declaration and implementation
//class Histogram {
//private:
//	template <typename T>
//	T roundToRange(T value, T min, T max, int bin) {
//
//	}
//public:
//	int bins;
//	Histogram(int bins) {
//		this->bins = bins;
//	};
//	template <typename T>
//	std::map<T, int> compute(std::vector<T> &vec) {
//		std::map<T, int> outHistogram;
//		auto minMax = std::minmax_element(vec.begin(), vec.end());
//		T min = *minMax.first;
//		T max = *minMax.second;
//		for (T element : vec) {
//			// linearly remap to between 0 and 1
//			// scale to 0 and bin size
//			// round to nearest
//			// scale back linearly to between min and 
//			auto v1 = (std::clamp(element, min, max) - min);
//			auto roundedElement = std::round(
//				(
//					v1 / ( max - min)
//					) * bins
//			);
//			roundedElement = ((roundedElement / bins) * (max - min)) + min;
//			T outElement = static_cast<T>(roundedElement);
//			outHistogram[outElement]++;
//		}
//		return outHistogram;
//	};
//};

// {1,2,3,4,5} bins = 3 {=> 1 => 2, 3 => 2, 5 => 1}
// {1,2,3,4,5,6,7} bins = 3 => {1 => 3, 4 => 3, 7 => 1}
template <typename T>
std::map<double, int> computeHistogram(std::vector<T>& vec, int bins) {
    std::map<double, int> out;
    if (vec.empty() || bins <= 0)
        return out;

    auto minmax = std::minmax_element(vec.begin(), vec.end());
    T min = *minmax.first;
    T max = *minmax.second;

    // If all elements are the same, assign them to one bin.
    if (min == max) {
        out[min] = vec.size();
        return out;
    }

    double binSize = static_cast<double>(max - min) / bins;
    for (T element : vec) {
        int binIndex = std::floor((element - min) / binSize);
        // Adjust for the maximum element falling exactly on the boundary.
        if (binIndex == bins)
            binIndex = bins - 1;
        double bin = (binIndex * binSize) + min;
        out[bin]++;
    }
    return out;
}
