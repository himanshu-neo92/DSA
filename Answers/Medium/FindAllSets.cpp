// Problem: Find All Subsets (Power Set)
// Given an array of numbers, return all possible subsets.
// [1,2,3] -> [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(2^n) - every element is either included or excluded
// Space Complexity: O(n) recursion depth + O(2^n * n) for output
//
// Key concepts:
// - Decision tree: include or exclude each element
// - Recursive DFS backtracking
// =======================================================

#include "TestBase.h"

namespace FindAllSets {

  void dfsCreate(const std::vector<int>& input, int index, std::vector<std::vector<int>>& res, std::vector<int>& subset ) {

    if ( index >= input.size()) {
      res.push_back(subset);
      return;
    }

    // Take the curr element
    subset.push_back(input[index]);
dfsCreate(input, index + 1, res, subset);

// don't take the curr element
subset.pop_back();
dfsCreate(input, index + 1, res, subset);

  }

   void createSubSets(const std::vector<int>& input, std::vector<std::vector<int>>& res) {

std::vector<int> subset;
dfsCreate(input, 0, res, subset);
  }

}

// ==================== TEST CASES ====================

TEST(FindAllSets_EmptyInput) {
    std::vector<int> input = {};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    TestBase::assertEqual(1, static_cast<int>(result.size()));
    TestBase::assertVectorEqual({}, result[0]);
}

TEST(FindAllSets_SingleElement) {
    std::vector<int> input = {1};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    TestBase::assertEqual(2, static_cast<int>(result.size()));
}

TEST(FindAllSets_TwoElements) {
    std::vector<int> input = {1, 2};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    TestBase::assertEqual(4, static_cast<int>(result.size()));
}

TEST(FindAllSets_ThreeElements) {
    std::vector<int> input = {1, 2, 3};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    TestBase::assertEqual(8, static_cast<int>(result.size()));
}

TEST(FindAllSets_ContainsEmptySet) {
    std::vector<int> input = {1, 2};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    bool hasEmpty = false;
    for (const auto& subset : result) {
        if (subset.empty()) {
            hasEmpty = true;
            break;
        }
    }
    TestBase::assertTrue(hasEmpty, "Result should contain empty set");
}

TEST(FindAllSets_ContainsFullSet) {
    std::vector<int> input = {1, 2, 3};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    bool hasFull = false;
    for (const auto& subset : result) {
        if (subset == input) {
            hasFull = true;
            break;
        }
    }
    TestBase::assertTrue(hasFull, "Result should contain the full set");
}

TEST(FindAllSets_FourElements) {
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    TestBase::assertEqual(16, static_cast<int>(result.size()));
}

TEST(FindAllSets_NegativeNumbers) {
    std::vector<int> input = {-1, -2};
    std::vector<std::vector<int>> result;
     FindAllSets::createSubSets(input, result);
    TestBase::assertEqual(4, static_cast<int>(result.size()));
}
