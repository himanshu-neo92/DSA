// Problem: Closest Two Elements in Array
// Given an array, find the pair of elements with the smallest absolute difference.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) - Sort then linear scan
// Space Complexity: O(1) - In-place sort
//
// Key concepts:
// - Sort the array
// - Closest pair must be adjacent after sorting
// - Single pass to find minimum difference
// =======================================================

#include "TestBase.h"
#include <algorithm>
#include <cmath>

namespace Closest2ElementsInArray {

// ========== Solution ==========
std::pair<int,int> closestPair(std::vector<int>& arr) {
    if (arr.size() < 2) return {0, 0};

    std::sort(arr.begin(), arr.end());

    int minDiff = std::abs(arr[1] - arr[0]);
    std::pair<int,int> result = {arr[0], arr[1]};

    for (size_t i = 2; i < arr.size(); ++i) {
        int diff = std::abs(arr[i] - arr[i - 1]);
        if (diff < minDiff) {
            minDiff = diff;
            result = {arr[i - 1], arr[i]};
        }
    }

    return result;
}

// ========== Tests ==========

TEST(ClosestPair_Basic) {
    std::vector<int> arr = {1, 5, 3, 19, 18, 25};
    auto result = closestPair(arr);
    TestBase::assertEqual(1, std::abs(result.second - result.first));
}

TEST(ClosestPair_Adjacent) {
    std::vector<int> arr = {1, 2, 3, 4};
    auto result = closestPair(arr);
    TestBase::assertEqual(1, std::abs(result.second - result.first));
}

TEST(ClosestPair_Duplicates) {
    std::vector<int> arr = {5, 3, 5, 10};
    auto result = closestPair(arr);
    TestBase::assertEqual(0, std::abs(result.second - result.first));
}

TEST(ClosestPair_Negative) {
    std::vector<int> arr = {-10, -5, 0, 100};
    auto result = closestPair(arr);
    TestBase::assertEqual(5, std::abs(result.second - result.first));
}

TEST(ClosestPair_TwoElements) {
    std::vector<int> arr = {7, 3};
    auto result = closestPair(arr);
    TestBase::assertEqual(4, std::abs(result.second - result.first));
}

TEST(ClosestPair_LargeGap) {
    std::vector<int> arr = {1, 1000000, 999999};
    auto result = closestPair(arr);
    TestBase::assertEqual(1, std::abs(result.second - result.first));
}

} // namespace Closest2ElementsInArray
