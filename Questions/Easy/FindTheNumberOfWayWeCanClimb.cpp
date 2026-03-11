// Problem: Find the Number of Ways We Can Climb Stairs
// Given n stairs, you can climb 1 or 2 stairs at a time.
// Return the number of distinct ways to reach the top.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single loop
// Space Complexity: O(1) - Only two variables
//
// This is equivalent to the Fibonacci sequence:
//   ways(1) = 1, ways(2) = 2, ways(n) = ways(n-1) + ways(n-2)
//
// Alternative approaches:
// - Recursive: O(2^n) time — exponential, never use
// - Recursive + Memo: O(n) time, O(n) space
// - DP array: O(n) time, O(n) space
// - Iterative (used here): O(n) time, O(1) space — optimal
// =======================================================

#include "TestBase.h"

namespace ClimbStairs {

// ========== Solution ==========
int climbStairs(int n) {
    // TODO: implement your solution here
    return 0;
}

// ========== Tests ==========

TEST(ClimbStairs_Base) {
    TestBase::assertEqual(1, climbStairs(1));
    TestBase::assertEqual(2, climbStairs(2));
}

TEST(ClimbStairs_Small) {
    TestBase::assertEqual(3, climbStairs(3));
    TestBase::assertEqual(5, climbStairs(4));
    TestBase::assertEqual(8, climbStairs(5));
}

TEST(ClimbStairs_Larger) {
    TestBase::assertEqual(13, climbStairs(6));
    TestBase::assertEqual(89, climbStairs(10));
    TestBase::assertEqual(987, climbStairs(15));
}

} // namespace ClimbStairs
