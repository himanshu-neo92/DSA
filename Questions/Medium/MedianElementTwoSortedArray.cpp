// Problem: Median of Two Sorted Arrays
// Find the median element of two sorted arrays.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(log(min(n,m))) - Binary search on the smaller array
// Space Complexity: O(1)
//
// Key concepts:
// - Binary search on partition position in the smaller array
// - Ensure left partitions of both arrays are <= right partitions
// - Handle odd/even total length for median calculation
//
// Hint: Select elements from both arrays such that left half count
// equals right half count, and all left elements <= all right elements.
// =======================================================

#include "TestBase.h"

namespace MedianElementTwoSortedArray {

// ========== Solution ==========
float findMedianOfTwoSortedArrays(const std::vector<int>& a, const std::vector<int>& b) {
    // TODO: implement your solution here
    return 0.0f;
}

// ========== Tests ==========
TEST(MedianElementTwoSortedArray_Odd) {
  TestBase::assertEqual(4.0f, findMedianOfTwoSortedArrays({1, 2, 3, 5}, {3, 4, 6, 9, 10}));
}

TEST(MedianElementTwoSortedArray_Even) {
  TestBase::assertEqual(4.0f, findMedianOfTwoSortedArrays({1, 3, 4, 5}, {1, 4, 5, 6}));
}

TEST(MedianElementTwoSortedArray_BothEmpty) {
  TestBase::assertEqual(0.0f, findMedianOfTwoSortedArrays({}, {}));
}

TEST(MedianElementTwoSortedArray_FirstEmpty) {
  TestBase::assertEqual(3.0f, findMedianOfTwoSortedArrays({}, {1, 2, 3, 4, 5}));
}

TEST(MedianElementTwoSortedArray_SecondEmpty) {
  TestBase::assertEqual(5.0f, findMedianOfTwoSortedArrays({2, 4, 6, 8}, {}));
}

TEST(MedianElementTwoSortedArray_SingleElementEach) {
  TestBase::assertEqual(2.0f, findMedianOfTwoSortedArrays({1}, {3}));
}

TEST(MedianElementTwoSortedArray_OneSingleElement) {
  TestBase::assertEqual(3.0f, findMedianOfTwoSortedArrays({3}, {1, 2, 4, 5}));
}

TEST(MedianElementTwoSortedArray_NoOverlapFirstSmaller) {
  TestBase::assertEqual(3.5f, findMedianOfTwoSortedArrays({1, 2, 3}, {4, 5, 6}));
}

TEST(MedianElementTwoSortedArray_NoOverlapSecondSmaller) {
  TestBase::assertEqual(6.5f, findMedianOfTwoSortedArrays({10, 20, 30}, {1, 2, 3}));
}

TEST(MedianElementTwoSortedArray_Duplicates) {
  TestBase::assertEqual(1.5f, findMedianOfTwoSortedArrays({1, 1, 2}, {1, 2, 2}));
}

TEST(MedianElementTwoSortedArray_NegativeNumbers) {
  TestBase::assertEqual(-0.5f, findMedianOfTwoSortedArrays({-5, -1, 2}, {-3, 0, 4}));
}

TEST(MedianElementTwoSortedArray_UnequalSizes) {
  TestBase::assertEqual(4.0f, findMedianOfTwoSortedArrays({1, 3, 5, 7}, {2, 4, 6}));
}

TEST(MedianElementTwoSortedArray_LargeSizeDifference) {
  TestBase::assertEqual(6.0f, findMedianOfTwoSortedArrays({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {100}));
}

} // namespace MedianElementTwoSortedArray
