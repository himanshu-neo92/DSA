// LeetCode 15 - 3Sum
// Given an integer array nums, return all triplets [nums[i], nums[j], nums[k]]
// such that i != j, i != k, j != k, and nums[i] + nums[j] + nums[k] == 0.
// The solution set must not contain duplicate triplets.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n²) - Sort + two-pointer sweep
// Space Complexity: O(1) - Excluding output
//
// Key concepts:
// - Sort the array first
// - Fix one element, use two pointers for the remaining pair
// - Skip duplicates to avoid duplicate triplets
// - Early termination: if nums[i] > 0, no valid triplet possible
// =======================================================

#include "TestBase.h"
#include <vector>
#include <algorithm>

namespace ThreeSum {

// ========== Solution ==========
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    // TODO: implement your solution here
    return {};
}

// ========== Tests ==========
TEST(ThreeSum_BasicExample) {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto result = threeSum(nums);
    TestBase::assertEqual(2, (int)result.size());
}

TEST(ThreeSum_NoSolution) {
    std::vector<int> nums = {0, 1, 1};
    auto result = threeSum(nums);
    TestBase::assertEqual(0, (int)result.size());
}

TEST(ThreeSum_AllZeros) {
    std::vector<int> nums = {0, 0, 0};
    auto result = threeSum(nums);
    TestBase::assertEqual(1, (int)result.size());
    TestBase::assertVectorEqual({0, 0, 0}, result[0]);
}

TEST(ThreeSum_Empty) {
    std::vector<int> nums = {};
    auto result = threeSum(nums);
    TestBase::assertEqual(0, (int)result.size());
}

TEST(ThreeSum_TwoElements) {
    std::vector<int> nums = {-1, 1};
    auto result = threeSum(nums);
    TestBase::assertEqual(0, (int)result.size());
}

} // namespace ThreeSum
