/*
Problem: Find All Subsets (Power Set)
Given an array of numbers, return all possible subsets.
[1,2,3] -> [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]

==================== PERFORMANCE ====================
Time Complexity:  O(2^n) - Total number of subsets
Space Complexity: O(n) - Recursion depth + current subset

Key concepts:
- Decision tree: for each element, either include or exclude
- Recursive DFS: branch on include/exclude at each index
- Base case: when index >= input.size(), add current subset to result
=======================================================
*/

#include "TestBase.h"

namespace FindAllSets {

// ========== Solution ==========
void dfsCreate(const std::vector<int>& input, int index, std::vector<std::vector<int>>& res, std::vector<int>& subset) {
    // TODO: implement DFS to generate all subsets
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
