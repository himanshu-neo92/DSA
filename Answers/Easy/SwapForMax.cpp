// Problem: Swap Digits for Maximum Number
// Given a number, perform at most one swap of two digits to produce
// the maximum possible number. 2279 -> 9272, 9973 -> 9973.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(d²) where d = number of digits (at most 6)
// Space Complexity: O(d) - digit array storage
//
// Key concepts:
// - Extract digits, scan from most significant digit
// - Find largest digit to the right and swap with first improvable position
// =======================================================

#include "TestBase.h"


namespace SwapForMax {

  int swapAndConvertToNumber( std::vector<int>& digits, const int i, const int j) {
    DEBUG_OUT("  swapAndConvertToNumber: swapping index " << i << " (value " << digits[i] << ") with index " << j << " (value " << digits[j] << ")");

    int temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;

    #ifdef DEBUG_OUTPUT
    std::cout << "[DEBUG]   Digits after swap: [";
    for (size_t k = 0; k < digits.size(); ++k) {
      std::cout << digits[k] << (k < digits.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    #endif

    int number = 0;

    for (int k = 0; k< digits.size(); ++k) {
      number += std::pow<int>(10, k) * digits[k];
    }

    DEBUG_OUT("  Converted number: " << number);
    return number;

  }

  int maxNumber(unsigned int number) {
    DEBUG_OUT("maxNumber called with: " << number);

    std::vector<int> digits;
    digits.reserve(6);
int tempNum = number;

int k = 0;
    while(tempNum > 0) {
      digits.push_back(tempNum % 10);
      ++k;
      tempNum /= 10;
    }

    #ifdef DEBUG_OUTPUT
    std::cout << "[DEBUG]   Digits (reversed): [";
    for (size_t k = 0; k < digits.size(); ++k) {
      std::cout << digits[k] << (k < digits.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    #endif

    const auto size = digits.size();
    DEBUG_OUT("  Searching for best swap...");
    for (int i = size - 1; i >= 0; --i) {
      int maxIndex = i;
      for ( int j = 0; j < i; ++j ) {
        if ( digits[j] > digits[maxIndex] ) {
          maxIndex = j;
        }
      }

      DEBUG_OUT("    i=" << i << ", digits[i]=" << digits[i] << ", maxIndex=" << maxIndex << ", digits[maxIndex]=" << digits[maxIndex]);

      if (digits[maxIndex] > digits[i]) {
        DEBUG_OUT("  Found swap opportunity!");
        return swapAndConvertToNumber(digits, i , maxIndex);
      }
    }

    DEBUG_OUT("  No swap needed, returning original: " << number);
    return number;
  }

}

// ==================== TEST CASES ====================
TEST(SwapForMax_BasicSwap) {
    int result = SwapForMax::maxNumber(2279);
    DEBUG_OUT("Input: 2279, Result: " << result << ", Expected: 9272");
    TestBase::assertEqual(9272, result);
}

TEST(SwapForMax_AlreadyMax) {
    int result = SwapForMax::maxNumber(9973);
    DEBUG_OUT("Input: 9973, Result: " << result << ", Expected: 9973");
    TestBase::assertEqual(9973, result);
}

TEST(SwapForMax_SingleDigit) {
    int result = SwapForMax::maxNumber(5);
    DEBUG_OUT("Input: 5, Result: " << result << ", Expected: 5");
    TestBase::assertEqual(5, result);
}

TEST(SwapForMax_TwoDigits) {
    int result = SwapForMax::maxNumber(19);
    DEBUG_OUT("Input: 19, Result: " << result << ", Expected: 91");
    TestBase::assertEqual(91, result);
}

TEST(SwapForMax_TwoDigitsNoSwap) {
    int result = SwapForMax::maxNumber(91);
    DEBUG_OUT("Input: 91, Result: " << result << ", Expected: 91");
    TestBase::assertEqual(91, result);
}

TEST(SwapForMax_AllSameDigits) {
    int result = SwapForMax::maxNumber(1111);
    DEBUG_OUT("Input: 1111, Result: " << result << ", Expected: 1111");
    TestBase::assertEqual(1111, result);
}

TEST(SwapForMax_SwapFirstAndLast) {
    int result = SwapForMax::maxNumber(1234);
    DEBUG_OUT("Input: 1234, Result: " << result << ", Expected: 4231");
    TestBase::assertEqual(4231, result);
}

TEST(SwapForMax_LargeNumber) {
    int result = SwapForMax::maxNumber(98368);
    DEBUG_OUT("Input: 98368, Result: " << result << ", Expected: 98863");
    TestBase::assertEqual(98863, result);
}

TEST(SwapForMax_SwapMiddleDigits) {
    int result = SwapForMax::maxNumber(9123);
    DEBUG_OUT("Input: 9123, Result: " << result << ", Expected: 9321");
    TestBase::assertEqual(9321, result);
}

TEST(SwapForMax_LeadingNines) {
    int result = SwapForMax::maxNumber(99123);
    DEBUG_OUT("Input: 99123, Result: " << result << ", Expected: 99321");
    TestBase::assertEqual(99321, result);
}
