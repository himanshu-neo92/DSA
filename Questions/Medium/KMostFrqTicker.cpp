// Problem: K Most Frequent Elements (LeetCode 347)
// Given an integer array and k, return the k most frequent elements.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Bucket sort approach
// Space Complexity: O(n) - Frequency map + buckets
//
// Key concepts:
// - Count frequencies with a hash map
// - Bucket sort: bucket[freq] = list of elements with that frequency
// - Iterate buckets from highest to lowest, collect k elements
//
// Alternative: O(n log k) with a min-heap of size k
// =======================================================

#include "TestBase.h"
#include <unordered_map>
#include <algorithm>

namespace KMostFrqTicker {

// ========== Solution ==========
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    // TODO: implement your solution here
    return {};
}

// ========== Tests ==========

TEST(TopKFrequent_Basic) {
    auto result = topKFrequent({1,1,1,2,2,3}, 2);
    TestBase::assertEqual(2, (int)result.size());
    std::sort(result.begin(), result.end());
    TestBase::assertVectorEqual({1, 2}, result);
}

TEST(TopKFrequent_Single) {
    auto result = topKFrequent({1}, 1);
    TestBase::assertEqual(1, (int)result.size());
    TestBase::assertEqual(1, result[0]);
}

TEST(TopKFrequent_AllSame) {
    auto result = topKFrequent({5,5,5,5}, 1);
    TestBase::assertEqual(1, (int)result.size());
    TestBase::assertEqual(5, result[0]);
}

TEST(TopKFrequent_KEqualsUnique) {
    auto result = topKFrequent({1,2,3}, 3);
    TestBase::assertEqual(3, (int)result.size());
}

TEST(TopKFrequent_NegativeNumbers) {
    auto result = topKFrequent({-1,-1,2,2,2,3}, 1);
    TestBase::assertEqual(1, (int)result.size());
    TestBase::assertEqual(2, result[0]);
}

TEST(TopKFrequent_Ties) {
    auto result = topKFrequent({1,1,2,2,3,3}, 2);
    TestBase::assertEqual(2, (int)result.size());
}

} // namespace KMostFrqTicker
