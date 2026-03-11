// Problem: Majority Element
// Given an array, find the element that occurs the most (more than n/2 times).
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single pass (Boyer-Moore Voting Algorithm)
// Space Complexity: O(1) - Only uses two variables
//
// Key concepts:
// - Boyer-Moore Voting Algorithm
// - Maintain a candidate and counter
// - If counter drops to 0, pick new candidate
// - The majority element will always survive
// =======================================================

#include "TestBase.h"

namespace MajorityElement {

// ========== Solution ==========
int findMajorityElement(const std::vector<int>& vec) {
    // TODO: implement your solution here
    return 0;
}

} // namespace MajorityElement

// ==================== TEST CASES ====================

TEST(MajorityElement_Basic) {
    const std::vector<int> vec = {1,1,2,3,2,2,1,2};
    const int ele = MajorityElement::findMajorityElement(vec);
    TestBase::assertEqual(2, ele);
}
