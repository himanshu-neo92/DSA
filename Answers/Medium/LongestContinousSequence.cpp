// Problem: Longest Continuous Sequence
// Given an unsorted list of numbers, find the length of the longest
// consecutive sequence. [1,4,6,2,9] -> 2 (sequence 1,2).
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - each element checked at most twice via hash set
// Space Complexity: O(n) - hash set storing all elements
//
// Key concepts:
// - Hash set for O(1) lookups
// - Expand backwards from each element to find sequence start
// =======================================================

#include "TestBase.h"
#include <unordered_set>

namespace LongestContinousSequence {

int longestContinousSeq(const std::vector<int>& nums) {
  DEBUG_OUT("longestContinousSeq called with " << nums.size() << " elements");

  #ifdef DEBUG_OUTPUT
  std::cout << "[DEBUG]   Input: [";
  for (size_t i = 0; i < nums.size(); ++i) {
    std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
  }
  std::cout << "]\n";
  #endif

  std::unordered_set<int> numSet(nums.begin(), nums.end());
  int maxSeq = 0;

  for (const auto v : nums) {
    int seq = 1;
    int numToChec = v - 1;

    DEBUG_OUT("  Processing value: " << v);

    while ( numSet.find(numToChec) != numSet.end() ) {
      DEBUG_OUT("    Found " << numToChec << " in set, extending sequence to " << (seq + 1));
      --numToChec;
      ++seq;
    }
    maxSeq = std::max(seq, maxSeq);

    DEBUG_OUT("  After inserting " << v << ": seq=" << seq << ", maxSeq=" << maxSeq);
  }

  DEBUG_OUT("Result: " << maxSeq);
  return maxSeq;
}

}

// ==================== TEST CASES ====================

TEST(LongestContinousSeq_BasicExample) {
    int result = LongestContinousSequence::longestContinousSeq({1, 4, 6, 2, 9});
    DEBUG_OUT("Input: {1,4,6,2,9}, Result: " << result << ", Expected: 2");
    TestBase::assertEqual(2, result);
}

TEST(LongestContinousSeq_LongerSequence) {
    int result = LongestContinousSequence::longestContinousSeq({100, 4, 200, 1, 3, 2});
    DEBUG_OUT("Input: {100,4,200,1,3,2}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(LongestContinousSeq_EmptyArray) {
    int result = LongestContinousSequence::longestContinousSeq({});
    DEBUG_OUT("Input: {}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(LongestContinousSeq_SingleElement) {
    int result = LongestContinousSequence::longestContinousSeq({42});
    DEBUG_OUT("Input: {42}, Result: " << result << ", Expected: 1");
    TestBase::assertEqual(1, result);
}

TEST(LongestContinousSeq_AllSame) {
    int result = LongestContinousSequence::longestContinousSeq({7, 7, 7, 7});
    DEBUG_OUT("Input: {7,7,7,7}, Result: " << result << ", Expected: 1");
    TestBase::assertEqual(1, result);
}

TEST(LongestContinousSeq_AlreadySorted) {
    int result = LongestContinousSequence::longestContinousSeq({1, 2, 3, 4, 5});
    DEBUG_OUT("Input: {1,2,3,4,5}, Result: " << result << ", Expected: 5");
    TestBase::assertEqual(5, result);
}

TEST(LongestContinousSeq_ReverseSorted) {
    int result = LongestContinousSequence::longestContinousSeq({5, 4, 3, 2, 1});
    DEBUG_OUT("Input: {5,4,3,2,1}, Result: " << result << ", Expected: 5");
    TestBase::assertEqual(5, result);
}

TEST(LongestContinousSeq_NegativeNumbers) {
    int result = LongestContinousSequence::longestContinousSeq({-3, -2, -1, 0, 1});
    DEBUG_OUT("Input: {-3,-2,-1,0,1}, Result: " << result << ", Expected: 5");
    TestBase::assertEqual(5, result);
}

TEST(LongestContinousSeq_DisjointSequences) {
    int result = LongestContinousSequence::longestContinousSeq({10, 11, 12, 1, 2, 20, 21, 22, 23});
    DEBUG_OUT("Input: {10,11,12,1,2,20,21,22,23}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(LongestContinousSeq_WithDuplicates) {
    int result = LongestContinousSequence::longestContinousSeq({1, 2, 2, 3, 4});
    DEBUG_OUT("Input: {1,2,2,3,4}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(LongestContinousSeq_TwoElements) {
    int result = LongestContinousSequence::longestContinousSeq({1, 2});
    DEBUG_OUT("Input: {1,2}, Result: " << result << ", Expected: 2");
    TestBase::assertEqual(2, result);
}

TEST(LongestContinousSeq_TwoElementsNotConsecutive) {
    int result = LongestContinousSequence::longestContinousSeq({1, 100});
    DEBUG_OUT("Input: {1,100}, Result: " << result << ", Expected: 1");
    TestBase::assertEqual(1, result);
}

TEST(LongestContinousSeq_LargeGaps) {
    int result = LongestContinousSequence::longestContinousSeq({0, 1000000, 2000000});
    DEBUG_OUT("Input: {0,1000000,2000000}, Result: " << result << ", Expected: 1");
    TestBase::assertEqual(1, result);
}
