/*
Problem: Longest Continuous Sequence
Given a list of numbers (unsorted), find the length of the longest
consecutive sequence.
[1,4,6,2,9] -> 2 (sequence: 1,2)

==================== PERFORMANCE ====================
Time Complexity:  O(n) - Using a hash set for O(1) lookups
Space Complexity: O(n) - Hash set stores all elements

Key concepts:
- Insert all numbers into a set
- For each number, check how far the sequence extends downward
- Track the maximum sequence length
=======================================================
*/

#include "TestBase.h"
#include <unordered_set>

namespace LongestContinousSequence {

// ========== Solution ==========
int longestContinousSeq(const std::vector<int>& nums) {
    // TODO: implement your solution here
    return 0;
}

}

// ==================== TEST CASES ====================

TEST(LongestContinousSeq_BasicExample) {
    int result = LongestContinousSequence::longestContinousSeq({1, 4, 6, 2, 9});
    TestBase::assertEqual(2, result);
}

TEST(LongestContinousSeq_LongerSequence) {
    int result = LongestContinousSequence::longestContinousSeq({100, 4, 200, 1, 3, 2});
    TestBase::assertEqual(4, result);
}

TEST(LongestContinousSeq_EmptyArray) {
    int result = LongestContinousSequence::longestContinousSeq({});
    TestBase::assertEqual(0, result);
}

TEST(LongestContinousSeq_SingleElement) {
    int result = LongestContinousSequence::longestContinousSeq({42});
    TestBase::assertEqual(1, result);
}

TEST(LongestContinousSeq_AllSame) {
    int result = LongestContinousSequence::longestContinousSeq({7, 7, 7, 7});
    TestBase::assertEqual(1, result);
}

TEST(LongestContinousSeq_AlreadySorted) {
    int result = LongestContinousSequence::longestContinousSeq({1, 2, 3, 4, 5});
    TestBase::assertEqual(5, result);
}

TEST(LongestContinousSeq_ReverseSorted) {
    int result = LongestContinousSequence::longestContinousSeq({5, 4, 3, 2, 1});
    TestBase::assertEqual(5, result);
}

TEST(LongestContinousSeq_NegativeNumbers) {
    int result = LongestContinousSequence::longestContinousSeq({-3, -2, -1, 0, 1});
    TestBase::assertEqual(5, result);
}

TEST(LongestContinousSeq_DisjointSequences) {
    int result = LongestContinousSequence::longestContinousSeq({10, 11, 12, 1, 2, 20, 21, 22, 23});
    TestBase::assertEqual(4, result);
}

TEST(LongestContinousSeq_WithDuplicates) {
    int result = LongestContinousSequence::longestContinousSeq({1, 2, 2, 3, 4});
    TestBase::assertEqual(4, result);
}

TEST(LongestContinousSeq_TwoElements) {
    int result = LongestContinousSequence::longestContinousSeq({1, 2});
    TestBase::assertEqual(2, result);
}

TEST(LongestContinousSeq_TwoElementsNotConsecutive) {
    int result = LongestContinousSequence::longestContinousSeq({1, 100});
    TestBase::assertEqual(1, result);
}

TEST(LongestContinousSeq_LargeGaps) {
    int result = LongestContinousSequence::longestContinousSeq({0, 1000000, 2000000});
    TestBase::assertEqual(1, result);
}
