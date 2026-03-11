// Problem: Product of Array Except Self
// Given an array of ints, return an array where each element is the product
// of all other elements. [1,2,3,9] -> [54, 27, 18, 6]
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - two passes (prefix and suffix products)
// Space Complexity: O(1) extra - output array reused for prefix, suffix in variable
//
// Key concepts:
// - Prefix product array built left-to-right
// - Suffix product accumulated right-to-left in a single variable
// =======================================================

#include "TestBase.h"

namespace ProductOfArrayExceptSelf {

  void bruteForce(const std::vector<int>& input, std::vector<int>& output) {

        for (int i =0; i<output.size(); ++i) {
          output[i] = 1;
        }

    for (int i =0; i<input.size(); ++i) {
      for (int j=0; j<input.size(); ++j) {
        if (i != j)
        output[i] *= input[j];
      }
    }
  }

  void optimalSoln(const std::vector<int>& input, std::vector<int>& output) {

    if (input.capacity() == 0 ||  output.capacity() == 0) {
      return;
    }

    //  update output as a pre product array
    // ele at i = prod of all elements before it
    output[0] = 1;

    // starting at the 2nd ele we mult the prev ele in output
    // which is the pre prod till that index -1 with the input
    // index - 1.
    for (int i = 1; i< input.size(); ++i) {
      output[i] = output[i-1] * input[i-1];
    }

    // in the same array multiplay it by post product
    int prod = 1;
    // starting at 2nd last ele we mult into the output array
    // prod is mult with the arrays ele and then with the output.
    for (int i = input.size() - 2; i >= 0; --i) {
      prod *= input[i + 1];
      output[i] *= prod;
    }
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
