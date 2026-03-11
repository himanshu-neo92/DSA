// Problem: Maximum Sum Sub-array (Maximum Sub-array Problem)
// Given an integer array, find the contiguous sub-array with the
// largest sum and return that sum. Uses Kadane's algorithm: track
// the current running sum and reset it when it drops below the
// next element.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n)
// Space Complexity: O(1)
//
// Key concepts: Kadane's algorithm, single-pass greedy/DP.
// Alternative: divide-and-conquer in O(n log n).
// =======================================================

#include "TestBase.h"

namespace MaxSumOfSubArray {

// [1, -4, 2, 1, -2, 5, -3] => 6
// we start with the first element as the current and max sum.
// we then either include the next element or restart the current sum with the next element
// Kadane's algorithm.
int maxSumOfSubArray(const int arr[], int n) {
  if (n == 0) return 0;

  int maxSum = arr[0];
  int currentSum = arr[0];

  for (int i = 1; i < n; ++i) {
    currentSum = std::max(arr[i], currentSum + arr[i]);
    maxSum = std::max(maxSum, currentSum);
  }

  return maxSum;
}

int maxSumOfSubArrayWithIndex(const int arr[], int n, int& start, int& end) {



  if ( n == 0 ) {
          start = -1;
    end = -1;
    return 0;
  }

        start = 0;
    end = 0;
  int currSum = arr[0];
  int maxSum = arr[0];
  int tempStart = 0;

  for (int i =1;i< n; ++i) {

      DEBUG_OUT("arr[i]: " << arr[i] << " currSum: " << currSum);

      // Resstart the sum if it is negative
      if(currSum < 0) {
        currSum = arr[i];
        tempStart = i;
      } else {
        // Include the next element
      currSum += arr[i];
    }

    // we get a sum greater than max we can cache this.
      DEBUG_OUT("currSum: " << currSum << " maxSum: " << maxSum);
    if ( currSum > maxSum) {
      maxSum = currSum;
      start = tempStart;
      end = i;

      DEBUG_OUT("start: " << start << " end: " << end);
    }
  }

  return maxSum;
}

// ========== Tests for maxSumOfSubArrayWithIndex ==========
TEST(MaxSumOfSubArrayWithIndex_WholeArray) {
  const int arr[] = {1, 2, 3, 4};
  int s = -1, e = -1;
  TestBase::assertEqual(10, maxSumOfSubArrayWithIndex(arr, 4, s, e));
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(3, e);
}

TEST(MaxSumOfSubArrayWithIndex_MixedWithMaxMiddle) {
  const int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int s = -1, e = -1;
  TestBase::assertEqual(6, maxSumOfSubArrayWithIndex(arr, 9, s, e)); // [4, -1, 2, 1]
  TestBase::assertEqual(3, s);
  TestBase::assertEqual(6, e);
}

TEST(MaxSumOfSubArrayWithIndex_AllNegatives) {
  const int arr[] = {-1, -2, -3};
  int s = -1, e = -1;
  TestBase::assertEqual(-1, maxSumOfSubArrayWithIndex(arr, 3, s, e));
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(0, e);
}

TEST(MaxSumOfSubArrayWithIndex_SingleElementPositive) {
  const int arr[] = {5};
  int s = -1, e = -1;
  TestBase::assertEqual(5, maxSumOfSubArrayWithIndex(arr, 1, s, e));
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(0, e);
}

TEST(MaxSumOfSubArrayWithIndex_AllZeros) {
  const int arr[] = {0, 0, 0};
  int s = -1, e = -1;
  TestBase::assertEqual(0, maxSumOfSubArrayWithIndex(arr, 3, s, e));
  // Any single zero subarray is optimal; implementation chooses first occurrence.
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(0, e);
}

TEST(MaxSumOfSubArrayWithIndex_MixedEndsNegative) {
  const int arr[] = {3, -2, 5, -1};
  int s = -1, e = -1;
  TestBase::assertEqual(6, maxSumOfSubArrayWithIndex(arr, 4, s, e)); // [3, -2, 5]
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(2, e);
}

TEST(MaxSumOfSubArrayWithIndex_SingleNegative) {
  const int arr[] = {-5};
  int s = -1, e = -1;
  TestBase::assertEqual(-5, maxSumOfSubArrayWithIndex(arr, 1, s, e));
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(0, e);
}

TEST(MaxSumOfSubArrayWithIndex_LongerMixed) {
  const int arr[] = {2, -1, 2, 3, 4, -5};
  int s = -1, e = -1;
  TestBase::assertEqual(10, maxSumOfSubArrayWithIndex(arr, 6, s, e)); // [2, -1, 2, 3, 4]
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(4, e);
}

TEST(MaxSumOfSubArrayWithIndex_EmptyArray) {
  const int arr[] = {};
  int s = 123, e = 456;
  TestBase::assertEqual(0, maxSumOfSubArrayWithIndex(arr, 0, s, e));
  TestBase::assertEqual(-1, s);
  TestBase::assertEqual(-1, e);
}

// ========== Tests ==========
TEST(MaxSumOfSubArray_WholeArray) {
  const int arr[] = {1, 2, 3, 4};
  TestBase::assertEqual(10, maxSumOfSubArray(arr, 4));
}

TEST(MaxSumOfSubArray_MixedWithMaxMiddle) {
  const int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  TestBase::assertEqual(6, maxSumOfSubArray(arr, 9)); // [4, -1, 2, 1]
}

TEST(MaxSumOfSubArray_AllNegatives) {
  const int arr[] = {-1, -2, -3};
  TestBase::assertEqual(-1, maxSumOfSubArray(arr, 3)); // max single element
}

TEST(MaxSumOfSubArray_SingleElementPositive) {
  const int arr[] = {5};
  TestBase::assertEqual(5, maxSumOfSubArray(arr, 1));
}

TEST(MaxSumOfSubArray_AllZeros) {
  const int arr[] = {0, 0, 0};
  TestBase::assertEqual(0, maxSumOfSubArray(arr, 3));
}

TEST(MaxSumOfSubArray_MixedEndsNegative) {
  const int arr[] = {3, -2, 5, -1};
  TestBase::assertEqual(6, maxSumOfSubArray(arr, 4)); // [3, -2, 5]
}

TEST(MaxSumOfSubArray_SingleNegative) {
  const int arr[] = {-5};
  TestBase::assertEqual(-5, maxSumOfSubArray(arr, 1));
}

TEST(MaxSumOfSubArray_LongerMixed) {
  const int arr[] = {2, -1, 2, 3, 4, -5};
  TestBase::assertEqual(10, maxSumOfSubArray(arr, 6)); // [2, -1, 2, 3, 4]
}

TEST(MaxSumOfSubArray_EmptyArray) {
  const int arr[] = {};
  TestBase::assertEqual(0, maxSumOfSubArray(arr, 0));
}

} // namespace MaxSumOfSubArray
