/*
Problem: Swap Digits for Maximum Number
Given a number, perform at most one swap of two digits to make the largest
possible number.
Constraint: 1 < n < 100000

Examples:
  2279 -> 9272 (swap 2 and 9)
  9973 -> 9973 (no swap needed)

==================== PERFORMANCE ====================
Time Complexity:  O(d²) where d = number of digits (at most 6)
Space Complexity: O(d) - Store digits in a vector

Key concepts:
- Extract digits into a vector
- From most significant digit, find the largest digit to its right
- If found larger, swap and return
- If no beneficial swap exists, return original number
=======================================================
*/

#include "TestBase.h"

namespace SwapForMax {

// ========== Solution ==========
int swapAndConvertToNumber(std::vector<int>& digits, const int i, const int j) {
    // TODO: swap digits[i] and digits[j], convert back to number
    return 0;
}

int maxNumber(unsigned int number) {
    // TODO: implement - find the best single swap for max number
    return number;
}

}

// ==================== TEST CASES ====================
TEST(SwapForMax_BasicSwap) {
    int result = SwapForMax::maxNumber(2279);
    TestBase::assertEqual(9272, result);
}

TEST(SwapForMax_AlreadyMax) {
    int result = SwapForMax::maxNumber(9973);
    TestBase::assertEqual(9973, result);
}

TEST(SwapForMax_SingleDigit) {
    int result = SwapForMax::maxNumber(5);
    TestBase::assertEqual(5, result);
}

TEST(SwapForMax_TwoDigits) {
    int result = SwapForMax::maxNumber(19);
    TestBase::assertEqual(91, result);
}

TEST(SwapForMax_TwoDigitsNoSwap) {
    int result = SwapForMax::maxNumber(91);
    TestBase::assertEqual(91, result);
}

TEST(SwapForMax_AllSameDigits) {
    int result = SwapForMax::maxNumber(1111);
    TestBase::assertEqual(1111, result);
}

TEST(SwapForMax_SwapFirstAndLast) {
    int result = SwapForMax::maxNumber(1234);
    TestBase::assertEqual(4231, result);
}

TEST(SwapForMax_LargeNumber) {
    int result = SwapForMax::maxNumber(98368);
    TestBase::assertEqual(98863, result);
}

TEST(SwapForMax_SwapMiddleDigits) {
    int result = SwapForMax::maxNumber(9123);
    TestBase::assertEqual(9321, result);
}

TEST(SwapForMax_LeadingNines) {
    int result = SwapForMax::maxNumber(99123);
    TestBase::assertEqual(99321, result);
}
