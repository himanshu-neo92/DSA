// Problem: Find the Element That Is Not Duplicate in an Array
// Given an array where every element appears twice except one, find the unique element
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single pass through the array
// Space Complexity: O(1) - Only a single integer variable used for accumulation
//
// Alternative approaches:
// - Hash set: O(n) time, O(n) space - Track seen elements, remove on second occurrence
// - Sorting: O(n log n) time, O(1) space - Sort then check adjacent pairs
// - Brute force: O(n²) time, O(1) space - For each element, count occurrences
//
// Why this approach is optimal:
// - XOR of a number with itself is 0, so all duplicates cancel out
// - XOR is associative and commutative, order doesn't matter
// - Achieves both optimal time O(n) and optimal space O(1) simultaneously
// =======================================================

#include "TestBase.h"

namespace FindTheElementThatIsNotDup {

  int findElementThatIsNotDup(int* arr, int size) {
    if (arr == nullptr || size == 0) {
      return 0;
    }

    int result = 0;
    for ( int i = 0; i< size; ++i) {
      result ^= arr[i];
    }

    return result;
  }


// ========== Tests ==========
TEST(FindTheElementThatIsNotDup_Simple) {
  int arr[] = {1,2,3,4,1,2,3};
  TestBase::assertEqual(4, findElementThatIsNotDup(arr, 7));

  int arr2[] = {1,2,3,4,1,2,3,4};
  TestBase::assertEqual(0, findElementThatIsNotDup(arr2, 8));
}

TEST(FindTheElementThatIsNotDup_Edge) {
  TestBase::assertEqual(0, findElementThatIsNotDup(nullptr, 0));
}


} // namespace FindTheElementThatIsNotDup
