// Problem: Majority Element
// Given an array, find the element that appears more than ⌊n/2⌋ times.
// Uses the Boyer-Moore Voting Algorithm: maintain a candidate and a
// counter — increment when the current element matches, decrement
// otherwise; reset candidate when counter hits zero.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n)
// Space Complexity: O(1)
//
// Key concepts: Boyer-Moore voting algorithm, single-pass.
// Alternative: sorting O(n log n), hash-map counting O(n) with O(n) space.
// =======================================================

#include "TestBase.h"

namespace MajorityElement {

  int findMajorityElement(const std::vector<int>& vec) {

    if ( vec.size() < 0) {
      return 0;
    }

    int ele = vec[0];
    int counter = 1;

    for (const auto& val : vec) {
      if ( val == ele) {
        counter++;
      } else {
        counter --;
      }

      if ( counter == 0 ) {
        counter++;
        ele = val;
      }
    }

    return ele;

  }

} // namespace MajorityElement


TEST(MajorityElement_Basic) {
    const std::vector<int> vec = {1,1,2,3,2,2,1,2};
    const int ele = MajorityElement::findMajorityElement(vec);
        TestBase::assertEqual(2, ele);
  }

TEST(MajorityElement_SingleElement) {
    const std::vector<int> vec = {7};
    TestBase::assertEqual(7, MajorityElement::findMajorityElement(vec));
}

TEST(MajorityElement_AllSame) {
    const std::vector<int> vec = {3, 3, 3, 3, 3};
    TestBase::assertEqual(3, MajorityElement::findMajorityElement(vec));
}

TEST(MajorityElement_ClearMajority) {
    const std::vector<int> vec = {2, 2, 2, 1, 1};
    TestBase::assertEqual(2, MajorityElement::findMajorityElement(vec));
}

TEST(MajorityElement_TwoElements) {
    const std::vector<int> vec = {5, 5};
    TestBase::assertEqual(5, MajorityElement::findMajorityElement(vec));
}
