// Problem: Find the Element That Is Not Duplicate in an Array
// Given an array of integers, find the element that is not a duplicate
// This can be used to find the missing duplicate element in an array.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single pass through the array
// Space Complexity: O(1) - Only uses a single variable
//
// Hint: Think about bitwise operations (XOR)
// =======================================================

#include "TestBase.h"

namespace FindTheElementThatIsNotDup {

// ========== Solution ==========
int findElementThatIsNotDup(int* arr, int size) {
    // TODO: implement your solution here
    return 0;
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
