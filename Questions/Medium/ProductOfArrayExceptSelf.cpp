/*
Problem: Product of Array Except Self
Given an array of integers, return an array where each element is the
product of all elements except itself.
[1,2,3,9] -> [54, 27, 18, 6]

==================== PERFORMANCE ====================
Brute Force: O(n²) time, O(1) space
Optimal:     O(n) time, O(1) extra space (output array doesn't count)

Key concepts:
- First pass: build prefix product array in output
  output[i] = product of all elements before i
- Second pass (reverse): multiply by suffix product
  Maintain running product from the right
=======================================================
*/

#include "TestBase.h"

namespace ProductOfArrayExceptSelf {

// ========== Solution ==========
void bruteForce(const std::vector<int>& input, std::vector<int>& output) {
    // TODO: implement O(n²) brute force approach
}

void optimalSoln(const std::vector<int>& input, std::vector<int>& output) {
    // TODO: implement O(n) prefix/suffix product approach
}

}

// ==================== TEST CASES ====================

TEST(OptimalSoln_BasicCase) {
    std::vector<int> input = {1, 2, 3, 9};
    std::vector<int> output(4);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {54, 27, 18, 6};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_TwoElements) {
    std::vector<int> input = {3, 5};
    std::vector<int> output(2);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {5, 3};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_WithZero) {
    std::vector<int> input = {1, 2, 0, 4};
    std::vector<int> output(4);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {0, 0, 8, 0};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_WithTwoZeros) {
    std::vector<int> input = {0, 2, 0, 4};
    std::vector<int> output(4);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {0, 0, 0, 0};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_AllOnes) {
    std::vector<int> input = {1, 1, 1, 1};
    std::vector<int> output(4);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {1, 1, 1, 1};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_NegativeNumbers) {
    std::vector<int> input = {-1, 2, -3, 4};
    std::vector<int> output(4);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {-24, 12, -8, 6};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_SingleElement) {
    std::vector<int> input = {5};
    std::vector<int> output(1);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {1};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_LargerArray) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> output(5);
    ProductOfArrayExceptSelf::optimalSoln(input, output);
    std::vector<int> expected = {120, 60, 40, 30, 24};
    TestBase::assertVectorEqual(expected, output);
}

TEST(OptimalSoln_MatchesBruteForce) {
    std::vector<int> input = {2, 3, 4, 5, 6};
    std::vector<int> output1(5);
    std::vector<int> output2(5);
    ProductOfArrayExceptSelf::bruteForce(input, output1);
    ProductOfArrayExceptSelf::optimalSoln(input, output2);
    TestBase::assertVectorEqual(output1, output2);
}
