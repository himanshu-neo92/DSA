// Problem: Median of Two Sorted Arrays
// Given two sorted arrays of sizes n and m, find the median of the
// combined sorted sequence. Uses a binary-search partitioning
// approach on the smaller array to achieve logarithmic time.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(log(min(n, m)))
// Space Complexity: O(1)
//
// Key concepts: binary search on partition index of the smaller array.
// Alternative: merge-based O(n + m), or full sort O((n+m) log(n+m)).
// =======================================================

#include "TestBase.h"

namespace MedianElementTwoSortedArray {

  float findMedianOfTwoSortedArrays(const std::vector<int>& a, const std::vector<int>& b) {
    // Ensure we binary-search on the smaller array
    if (a.size() > b.size()) {
      return findMedianOfTwoSortedArrays(b, a);
    }

    int n = a.size(), m = b.size();
    if (n == 0 && m == 0) return 0.0f;

    int lo = 0, hi = n;
    int half = (n + m + 1) / 2;

    while (lo <= hi) {
      int i = (lo + hi) / 2;   // partition in a: i elements on left
      int j = half - i;        // partition in b: j elements on left

      int aLeft  = (i == 0) ? std::numeric_limits<int>::min() : a[i - 1];
      int aRight = (i == n) ? std::numeric_limits<int>::max() : a[i];
      int bLeft  = (j == 0) ? std::numeric_limits<int>::min() : b[j - 1];
      int bRight = (j == m) ? std::numeric_limits<int>::max() : b[j];

      if (aLeft <= bRight && bLeft <= aRight) {
        if ((n + m) % 2 == 1) {
          return static_cast<float>(std::max(aLeft, bLeft));
        }
        return (std::max(aLeft, bLeft) + std::min(aRight, bRight)) / 2.0f;
      } else if (aLeft > bRight) {
        hi = i - 1;
      } else {
        lo = i + 1;
      }
    }

    return 0.0f;
  }

// ========== Tests ==========
TEST(MedianElementTwoSortedArray_Odd) {
  // 1, 2, 3, 3, 4, 5, 6, 9, 10
  TestBase::assertEqual(4.0f, findMedianOfTwoSortedArrays({1, 2, 3, 5}, {3, 4, 6, 9, 10}));
}

TEST(MedianElementTwoSortedArray_Even) {
  // 1, 1, 3, 4, 4, 5, 5, 6
  TestBase::assertEqual(4.0f, findMedianOfTwoSortedArrays({1, 3, 4, 5}, {1, 4, 5, 6}));
}

TEST(MedianElementTwoSortedArray_BothEmpty) {
  TestBase::assertEqual(0.0f, findMedianOfTwoSortedArrays({}, {}));
}

TEST(MedianElementTwoSortedArray_FirstEmpty) {
  // Median of {1, 2, 3, 4, 5} = 3
  TestBase::assertEqual(3.0f, findMedianOfTwoSortedArrays({}, {1, 2, 3, 4, 5}));
}

TEST(MedianElementTwoSortedArray_SecondEmpty) {
  // Median of {2, 4, 6, 8} = (4 + 6) / 2 = 5
  TestBase::assertEqual(5.0f, findMedianOfTwoSortedArrays({2, 4, 6, 8}, {}));
}

TEST(MedianElementTwoSortedArray_SingleElementEach) {
  // Median of {1, 3} = 2
  TestBase::assertEqual(2.0f, findMedianOfTwoSortedArrays({1}, {3}));
}

TEST(MedianElementTwoSortedArray_OneSingleElement) {
  // Merged: {1, 2, 3, 4, 5} -> Median = 3
  TestBase::assertEqual(3.0f, findMedianOfTwoSortedArrays({3}, {1, 2, 4, 5}));
}

TEST(MedianElementTwoSortedArray_NoOverlapFirstSmaller) {
  // Merged: {1, 2, 3, 4, 5, 6} -> Median = (3 + 4) / 2 = 3.5
  TestBase::assertEqual(3.5f, findMedianOfTwoSortedArrays({1, 2, 3}, {4, 5, 6}));
}

TEST(MedianElementTwoSortedArray_NoOverlapSecondSmaller) {
  // Merged: {1, 2, 3, 10, 20, 30} -> Median = (3 + 10) / 2 = 6.5
  TestBase::assertEqual(6.5f, findMedianOfTwoSortedArrays({10, 20, 30}, {1, 2, 3}));
}

TEST(MedianElementTwoSortedArray_Duplicates) {
  // Merged: {1, 1, 1, 2, 2, 2} -> Median = (1 + 2) / 2 = 1.5
  TestBase::assertEqual(1.5f, findMedianOfTwoSortedArrays({1, 1, 2}, {1, 2, 2}));
}

TEST(MedianElementTwoSortedArray_NegativeNumbers) {
  // Merged: {-5, -3, -1, 0, 2, 4} -> Median = (-1 + 0) / 2 = -0.5
  TestBase::assertEqual(-0.5f, findMedianOfTwoSortedArrays({-5, -1, 2}, {-3, 0, 4}));
}

TEST(MedianElementTwoSortedArray_UnequalSizes) {
  // Merged: {1, 2, 3, 4, 5, 6, 7} -> Median = 4
  TestBase::assertEqual(4.0f, findMedianOfTwoSortedArrays({1, 3, 5, 7}, {2, 4, 6}));
}

TEST(MedianElementTwoSortedArray_LargeSizeDifference) {
  // Merged: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100} -> Median = 6
  TestBase::assertEqual(6.0f, findMedianOfTwoSortedArrays({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {100}));
}

} // namespace MedianElementTwoSortedArray
