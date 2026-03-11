// Problem: Maximum Sum of Subarray (Kadane's Algorithm)
// Given an array, find the contiguous subarray with the largest sum.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single pass through the array
// Space Complexity: O(1) - Only uses two variables
//
// Key concepts:
// - Kadane's Algorithm
// - At each position: either extend the current subarray or start new
// - currentSum = max(arr[i], currentSum + arr[i])
// - Track the global maximum
//
// Variant: maxSumOfSubArrayWithIndex also returns the start and end indices
// =======================================================

#include "TestBase.h"

namespace MaxSumOfSubArray {

// ========== Solution ==========
int maxSumOfSubArray(const int arr[], int n) {
    // TODO: implement Kadane's algorithm
    return 0;
}

int maxSumOfSubArrayWithIndex(const int arr[], int n, int& start, int& end) {
    // TODO: implement Kadane's algorithm that also tracks start/end indices
    start = -1;
    end = -1;
    return 0;
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
  TestBase::assertEqual(6, maxSumOfSubArrayWithIndex(arr, 9, s, e));
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
  TestBase::assertEqual(0, s);
  TestBase::assertEqual(0, e);
}

TEST(MaxSumOfSubArrayWithIndex_MixedEndsNegative) {
  const int arr[] = {3, -2, 5, -1};
  int s = -1, e = -1;
  TestBase::assertEqual(6, maxSumOfSubArrayWithIndex(arr, 4, s, e));
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
  TestBase::assertEqual(10, maxSumOfSubArrayWithIndex(arr, 6, s, e));
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

// ========== Tests for maxSumOfSubArray ==========
TEST(MaxSumOfSubArray_WholeArray) {
  const int arr[] = {1, 2, 3, 4};
  TestBase::assertEqual(10, maxSumOfSubArray(arr, 4));
}

TEST(MaxSumOfSubArray_MixedWithMaxMiddle) {
  const int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  TestBase::assertEqual(6, maxSumOfSubArray(arr, 9));
}

TEST(MaxSumOfSubArray_AllNegatives) {
  const int arr[] = {-1, -2, -3};
  TestBase::assertEqual(-1, maxSumOfSubArray(arr, 3));
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
  TestBase::assertEqual(6, maxSumOfSubArray(arr, 4));
}

TEST(MaxSumOfSubArray_SingleNegative) {
  const int arr[] = {-5};
  TestBase::assertEqual(-5, maxSumOfSubArray(arr, 1));
}

TEST(MaxSumOfSubArray_LongerMixed) {
  const int arr[] = {2, -1, 2, 3, 4, -5};
  TestBase::assertEqual(10, maxSumOfSubArray(arr, 6));
}

TEST(MaxSumOfSubArray_EmptyArray) {
  const int arr[] = {};
  TestBase::assertEqual(0, maxSumOfSubArray(arr, 0));
}

} // namespace MaxSumOfSubArray
