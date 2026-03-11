// Problem: 0/1 Knapsack
// Given a bag of size k and elements of weight w and price p
// we need to maximise the profit so the value in the bag is max.
// This is a DP problem, solved by creating a weight x bag size matrix.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n * capacity) - Fill the DP table
// Space Complexity: O(n * capacity) - 2D DP table
//
// Key concepts:
// - Dynamic Programming (bottom-up)
// - For each item, decide: include it or skip it
// - DP[i][j] = max value using first i items with capacity j
// - If weight[i-1] > j: can't include, DP[i][j] = DP[i-1][j]
// - Else: DP[i][j] = max(DP[i-1][j], val[i-1] + DP[i-1][j-weight[i-1]])
// =======================================================

#include "TestBase.h"

namespace Knacksack {

// ========== Solution ==========
int maxProfit(const int cap, const std::vector<int>& weight, const std::vector<int>& val, const int n) {
    // TODO: implement your solution here
    return 0;
}

} // namespace Knacksack

// ==================== TEST CASES ====================

TEST(Knapsack_BasicCase) {
    std::vector<int> weight = {10, 20, 30};
    std::vector<int> val = {60, 100, 120};
    int capacity = 50;
    int n = 3;
    int result = Knacksack::maxProfit(capacity, weight, val, n);
    TestBase::assertEqual(220, result);
}

TEST(Knapsack_SingleItem_Fits) {
    std::vector<int> weight = {10};
    std::vector<int> val = {100};
    int capacity = 10;
    int result = Knacksack::maxProfit(capacity, weight, val, 1);
    TestBase::assertEqual(100, result);
}

TEST(Knapsack_SingleItem_DoesNotFit) {
    std::vector<int> weight = {20};
    std::vector<int> val = {100};
    int capacity = 10;
    int result = Knacksack::maxProfit(capacity, weight, val, 1);
    TestBase::assertEqual(0, result);
}

TEST(Knapsack_ZeroCapacity) {
    std::vector<int> weight = {10, 20, 30};
    std::vector<int> val = {60, 100, 120};
    int result = Knacksack::maxProfit(0, weight, val, 3);
    TestBase::assertEqual(0, result);
}

TEST(Knapsack_AllItemsFit) {
    std::vector<int> weight = {1, 2, 3};
    std::vector<int> val = {10, 20, 30};
    int capacity = 10;
    int result = Knacksack::maxProfit(capacity, weight, val, 3);
    TestBase::assertEqual(60, result);
}

TEST(Knapsack_ChooseBetterValue) {
    std::vector<int> weight = {5, 4, 6, 3};
    std::vector<int> val = {10, 40, 30, 50};
    int capacity = 10;
    int result = Knacksack::maxProfit(capacity, weight, val, 4);
    TestBase::assertEqual(90, result);
}

TEST(Knapsack_LargeCapacity) {
    std::vector<int> weight = {2, 3, 4, 5};
    std::vector<int> val = {3, 4, 5, 6};
    int capacity = 5;
    int result = Knacksack::maxProfit(capacity, weight, val, 4);
    TestBase::assertEqual(7, result);
}

TEST(Knapsack_EqualWeightsAndValues) {
    std::vector<int> weight = {5, 5, 5, 5};
    std::vector<int> val = {10, 10, 10, 10};
    int capacity = 15;
    int result = Knacksack::maxProfit(capacity, weight, val, 4);
    TestBase::assertEqual(30, result);
}

TEST(Knapsack_NoItems) {
    std::vector<int> weight = {};
    std::vector<int> val = {};
    int capacity = 50;
    int result = Knacksack::maxProfit(capacity, weight, val, 0);
    TestBase::assertEqual(0, result);
}

TEST(Knapsack_HighValueLowWeight) {
    std::vector<int> weight = {1, 2, 3, 8, 7, 4};
    std::vector<int> val = {20, 5, 10, 40, 15, 25};
    int capacity = 10;
    int result = Knacksack::maxProfit(capacity, weight, val, 6);
    TestBase::assertEqual(60, result);
}
