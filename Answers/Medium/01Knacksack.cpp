// Problem: 0/1 Knapsack
// Given a bag of capacity k and n items each with a weight and a value,
// select items (each at most once) to maximise total value without
// exceeding the bag's capacity. Classic dynamic-programming problem
// solved by building a (n+1) x (cap+1) DP table.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n * cap)
// Space Complexity: O(n * cap)
//
// Key concepts: bottom-up DP, 2-D table over items × capacity.
// Alternative: space-optimised to O(cap) using a single row.
// =======================================================

#include "TestBase.h"


namespace Knacksack {

  int maxProfit(const int cap, const std::vector<int>& weight, const std::vector<int>& val, const int n) {

    int DP[n + 1][cap + 1];
    for (int i =0; i<= n; ++i) {
      for (int j = 0; j <= cap; ++j) {
        if (i ==0 || j ==0) {
          DP[i][j] = 0;
        }
        else if (weight[i -1] > j) {
          DP[i][j] = DP[i-1][j];
        }
        else {
          DP[i][j] = std::max(DP[i-1][j], val[i-1] + DP[i-1][j - weight[i-1]]);
        }
      }

    }

return DP[n][cap];

  }



} // Knacksack

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
