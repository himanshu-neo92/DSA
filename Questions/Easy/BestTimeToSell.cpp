/*
Problem: Best Time to Buy and Sell Stock
Given an array of prices where price[i] is the price of the stock on day i,
find the maximum profit. Two variants:
1. Only 1 buy and 1 sell allowed
2. As many buys and sells as you want

==================== PERFORMANCE ====================
Variant 1 (single buy/sell):
  Time Complexity:  O(n) - Single pass tracking minimum price
  Space Complexity: O(1)

Variant 2 (multiple buy/sell):
  Time Complexity:  O(n) - Capture every upward price movement
  Space Complexity: O(1)
=======================================================
*/
#include "TestBase.h"

namespace BestTimeToSell {

// ========== Solution ==========
int maxProfit(const std::vector<int>& prices) {
    // TODO: implement single buy/sell variant
    return 0;
}

int maxProfitMultiBuy(const std::vector<int>& prices) {
    // TODO: implement multiple buy/sell variant
    return 0;
}

}

// ---------- maxProfit (single buy/sell) ----------

TEST(BestTimeToSell_SingleBuy_BasicExample) {
    int result = BestTimeToSell::maxProfit({7, 1, 5, 3, 6, 4});
    TestBase::assertEqual(5, result);
}

TEST(BestTimeToSell_SingleBuy_DecreasingPrices) {
    int result = BestTimeToSell::maxProfit({7, 6, 4, 3, 1});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_EmptyArray) {
    int result = BestTimeToSell::maxProfit({});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_SingleElement) {
    int result = BestTimeToSell::maxProfit({5});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_TwoElements_Profit) {
    int result = BestTimeToSell::maxProfit({1, 5});
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_SingleBuy_TwoElements_NoProfit) {
    int result = BestTimeToSell::maxProfit({5, 1});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_AllSamePrice) {
    int result = BestTimeToSell::maxProfit({3, 3, 3, 3});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_IncreasingPrices) {
    int result = BestTimeToSell::maxProfit({1, 2, 3, 4, 5});
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_SingleBuy_MinAtEnd) {
    int result = BestTimeToSell::maxProfit({3, 1, 8, 2, 5, 0});
    TestBase::assertEqual(7, result);
}

TEST(BestTimeToSell_SingleBuy_MaxAtStart) {
    int result = BestTimeToSell::maxProfit({10, 1, 2, 3, 4});
    TestBase::assertEqual(3, result);
}

TEST(BestTimeToSell_SingleBuy_VShapedPrices) {
    int result = BestTimeToSell::maxProfit({8, 5, 3, 1, 6, 10});
    TestBase::assertEqual(9, result);
}

TEST(BestTimeToSell_SingleBuy_LargeSpread) {
    int result = BestTimeToSell::maxProfit({1, 100000});
    TestBase::assertEqual(99999, result);
}

// ---------- maxProfitMultiBuy (multiple buys/sells) ----------

TEST(BestTimeToSell_MultiBuy_BasicExample) {
    int result = BestTimeToSell::maxProfitMultiBuy({7, 1, 5, 3, 6, 4});
    TestBase::assertEqual(7, result);
}

TEST(BestTimeToSell_MultiBuy_AllIncreasing) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 2, 3, 4, 5});
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_MultiBuy_AllDecreasing) {
    int result = BestTimeToSell::maxProfitMultiBuy({5, 4, 3, 2, 1});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_EmptyArray) {
    int result = BestTimeToSell::maxProfitMultiBuy({});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_SingleElement) {
    int result = BestTimeToSell::maxProfitMultiBuy({5});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_TwoElements_Profit) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 5});
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_MultiBuy_TwoElements_NoProfit) {
    int result = BestTimeToSell::maxProfitMultiBuy({5, 1});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_AllSamePrice) {
    int result = BestTimeToSell::maxProfitMultiBuy({3, 3, 3, 3});
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_ZigZag) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 5, 2, 8});
    TestBase::assertEqual(10, result);
}

TEST(BestTimeToSell_MultiBuy_MultipleValleysAndPeaks) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 4, 2, 7, 3, 9});
    TestBase::assertEqual(14, result);
}

TEST(BestTimeToSell_MultiBuy_LargeSpread) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 100000});
    TestBase::assertEqual(99999, result);
}

TEST(BestTimeToSell_MultiBuy_SingleTransaction_SameAsSingle) {
    int result = BestTimeToSell::maxProfitMultiBuy({7, 6, 4, 3, 1, 10});
    TestBase::assertEqual(9, result);
}
