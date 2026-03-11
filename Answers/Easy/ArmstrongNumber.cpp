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
//
// Performance concerns in current implementation:
// - std::pow is expensive (floating point operation)
// - Vector allocation has overhead
// - std::transform + std::accumulate = 2 passes over digits
//
// Suggested optimization:
//   int sum = 0, temp = n, digits = countDigits(n);
//   while (temp > 0) { sum += intPow(temp % 10, digits); temp /= 10; }
//   return sum == n;
// =======================================================

#include "TestBase.h"
#include <numeric>
#include <vector>

namespace ArmstrongNumber {

// ========== Solution ==========
  bool isAmstrongNumber(const int n) {
    if(n == 0) {
      return true;
    }
    if(n < 0) {
      return false;
    }
    int temp = n;
    std::vector<int> digits;
    digits.reserve(10);
    while (temp > 0) {
      digits.push_back(temp%10);
      temp /= 10;
    }

    const int pow = digits.size();
    std::transform(digits.begin(), digits.end(), digits.begin(), [pow](int n) { return std::pow<int>(n,pow); });

    const int sum = std::accumulate(digits.begin(), digits.end(), 0);

    return sum == n ? true : false;
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
