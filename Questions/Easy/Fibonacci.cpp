// Problem: Fibonacci
// Return the nth Fibonacci number
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single loop from 2 to n
// Space Complexity: O(1) - Only uses 3 variables (prev, curr, next)
//
// Alternative approaches:
// - Recursive (naive): O(2^n) time, O(n) space - Exponential! Never use.
// - Recursive + Memoization: O(n) time, O(n) space - Good but uses stack
// - Matrix exponentiation: O(log n) time, O(1) space - Optimal for very large n
// - Binet's formula: O(1) time - But loses precision for large n
//
// Why this approach is optimal for most cases:
// - Iterative avoids stack overflow for large n
// - O(1) space is cache-friendly
// - Simple and predictable performance
//
// Overflow considerations:
// - int overflows at fib(46) = 1,836,311,903
// - Use long long for fib up to 92
// - Use unsigned long long or BigInt for larger values
// =======================================================

#include "TestBase.h"

namespace Fibonacci {

// ========== Solution ==========
int fibonacci(int n) {
    // TODO: implement your solution here
    return 0;
}

// ========== Tests ==========
TEST(Fibonacci_BaseCases) {
    TestBase::assertEqual(0, fibonacci(0));
    TestBase::assertEqual(1, fibonacci(1));
}

TEST(Fibonacci_SmallNumbers) {
    TestBase::assertEqual(1, fibonacci(2));
    TestBase::assertEqual(2, fibonacci(3));
    TestBase::assertEqual(3, fibonacci(4));
    TestBase::assertEqual(5, fibonacci(5));
    TestBase::assertEqual(8, fibonacci(6));
    TestBase::assertEqual(13, fibonacci(7));
    TestBase::assertEqual(21, fibonacci(8));
}

TEST(Fibonacci_LargerNumbers) {
    TestBase::assertEqual(55, fibonacci(10));
    TestBase::assertEqual(610, fibonacci(15));
    TestBase::assertEqual(75025, fibonacci(25));
}

} // namespace Fibonacci
