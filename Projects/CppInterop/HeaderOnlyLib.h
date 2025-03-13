#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * @brief Computes the occurrence of values in a vec and bucket them into equally sized bins.
 * @tparam T The type of each vector element.
 * @param vec The input vector to base the histogram upon.
 * @param bins The number of bins in the histogram.
 * @return A map of bin and count. The range of bin i is from i to (not including) i+1.
 *
 * ```
 * std::vector<int> vec = {1,2,3,4,5};
 * int bins = 3;
 * auto result = computeHistogram(vec, bins);
 *
 * // Expected output:
 * // {1 => 2, 3 => 2, 5 => 1}
 * std::vector<int> vec = {1,2,3,4,5,6,7};
 * auto result = computeHistogram(vec, bins);
 *
 * // Expected output:
 * // {1 => 3, 4 => 3, 7 => 1}
 * ```
 */
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
