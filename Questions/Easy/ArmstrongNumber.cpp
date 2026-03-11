// Problem: ArmstrongNumber
// Return true if the given number is an Armstrong number
// (Sum of digits each raised to power of number of digits equals the number)
// Example: 153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(d) where d = number of digits (log₁₀(n))
// Space Complexity: O(d) - Vector stores all digits
//
// Alternative approaches:
// - Calculate without storing digits: O(d) time, O(1) space
//   (Count digits first, then compute sum in second pass)
// - String conversion: O(d) time, O(d) space - Less efficient
//
// Potential optimizations:
// - Avoid vector allocation by computing in-place
// - Use integer pow instead of std::pow (floating point)
// - std::pow returns double, may have precision issues for large numbers
// =======================================================

#include "TestBase.h"
#include <numeric>
#include <vector>

namespace ArmstrongNumber {

// ========== Solution ==========
bool isAmstrongNumber(const int n) {
    // TODO: implement your solution here
    return false;
}

// ========== Tests ==========
TEST(ArmstrongNumber_153) {
  TestBase::assertEqual(true, isAmstrongNumber(153));
  TestBase::assertEqual(true, isAmstrongNumber(9474));
}

TEST(ArmstrongNumber_123_NotArmstrong) {
  TestBase::assertEqual(false, isAmstrongNumber(123));
}

} // namespace ArmstrongNumber
