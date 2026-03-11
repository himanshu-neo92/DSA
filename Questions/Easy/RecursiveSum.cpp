// Problem: Recursive Sum
// Sum two non-negative integers digit by digit using recursion (no loops allowed).
// Each digit position is summed individually, carrying over when the sum >= 10.
// Return the resulting sum as an integer.
//
// Example:
//   recursiveSum(123, 456) => 579
//   recursiveSum(99, 1)    => 100
//   recursiveSum(0, 0)     => 0
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(max(d1, d2)) - where d1, d2 are the number of digits in each number
// Space Complexity: O(max(d1, d2)) - recursion stack depth proportional to number of digits
//
// Alternative approaches:
// - Simple addition (a + b): O(1) time, O(1) space - Trivial but misses the point
// - Iterative digit-by-digit: O(d) time, O(1) space - Uses a loop, not allowed here
// - String-based addition: O(d) time, O(d) space - Converts to strings, unnecessary overhead
//
// Why this approach:
// - Practices recursion fundamentals (base case + recursive step)
// - Demonstrates how carry propagation works at the digit level
// - Mirrors how hardware adders process numbers bit by bit
//
// Constraints:
// - Both inputs are non-negative integers
// - No loops (for, while, do-while) are allowed
// - Must use recursion to process digits
// =======================================================

#include "TestBase.h"

namespace RecursiveSum {

// ========== Solution ==========
int recursiveSum(int a, int b, int carry = 0) {
    // TODO: implement your solution here
    // Hint: extract the last digit of each number, sum them with carry,
    //       then recurse on the remaining digits.
    return 0;
}

// ========== Tests ==========
TEST(RecursiveSum_BothZero) {
    TestBase::assertEqual(0, recursiveSum(0, 0));
}

TEST(RecursiveSum_OneZero) {
    TestBase::assertEqual(5, recursiveSum(5, 0));
    TestBase::assertEqual(5, recursiveSum(0, 5));
}

TEST(RecursiveSum_NoCarry) {
    TestBase::assertEqual(579, recursiveSum(123, 456));
    TestBase::assertEqual(246, recursiveSum(123, 123));
}

TEST(RecursiveSum_WithCarry) {
    TestBase::assertEqual(100, recursiveSum(99, 1));
    TestBase::assertEqual(1000, recursiveSum(999, 1));
    TestBase::assertEqual(198, recursiveSum(99, 99));
}

TEST(RecursiveSum_DifferentLengths) {
    TestBase::assertEqual(110, recursiveSum(100, 10));
    TestBase::assertEqual(1005, recursiveSum(1000, 5));
    TestBase::assertEqual(1234, recursiveSum(1230, 4));
}

TEST(RecursiveSum_LargerNumbers) {
    TestBase::assertEqual(11110, recursiveSum(5555, 5555));
    TestBase::assertEqual(99999, recursiveSum(12345, 87654));
}

} // namespace RecursiveSum
