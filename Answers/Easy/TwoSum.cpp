// Problem: Two Sum
// Given an array of integers and a target, return indices of two numbers that add up to target
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single pass through the array
// Space Complexity: O(n) - Hash map stores up to n elements
//
// Alternative approaches:
// - Brute force: O(n²) time, O(1) space - Check all pairs
// - Sort + Two pointers: O(n log n) time, O(1) space - But loses original indices
//
// Why this approach is optimal:
// - Hash map provides O(1) average lookup for complement
// - Single pass means we find the answer as soon as possible
// - Trade-off: Uses extra memory for the hash map
//
// Cache considerations:
// - unordered_map has good cache locality for small maps
// - For very large arrays, consider cache-oblivious alternatives
// =======================================================

#include "TestBase.h"
#include <vector>
#include <unordered_map>

namespace TwoSum {

// ========== Solution ==========
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); i++) {
        const int complement = target - nums[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}

// ========== Tests ==========
TEST(TwoSum_Basic) {
    std::vector<int> nums = {2, 7, 11, 15};
    auto result = twoSum(nums, 9);
    TestBase::assertVectorEqual({0, 1}, result);
}

TEST(TwoSum_MiddleElements) {
    std::vector<int> nums = {3, 2, 4};
    auto result = twoSum(nums, 6);
    TestBase::assertVectorEqual({1, 2}, result);
}

} // namespace TwoSum
