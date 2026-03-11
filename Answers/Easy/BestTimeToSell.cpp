// Problem: Best Time to Buy and Sell Stock
// Given an array of prices where price[i] is the stock price on day i,
// find the best time to sell for:
// 1. Only 1 buy and 1 sell
// 2. As many buys and sells as desired
//
// ==================== PERFORMANCE ====================
// Single transaction:   O(n) time, O(1) space
// Multiple transactions: O(n) time, O(1) space
//
// Key concepts:
// - Track running minimum price for single transaction
// - Accumulate every upward price movement for multi-buy
// =======================================================
#include "TestBase.h"


namespace BestTimeToSell {

int maxProfit(const std::vector<int>& prices) {

  int maxProfit = 0;
  int lowestPrice = INT_MAX;

  for ( const auto& p : prices) {
    if ( p < lowestPrice) {
      lowestPrice = p;
    } else {
      const int price = p - lowestPrice;
      maxProfit = std::max(price, maxProfit);
    }
  }
  return maxProfit;
}

int maxProfitMultiBuy(const std::vector<int>& prices) {

  if ( prices.size() == 0) {
    return 0;
  }
  int maxProfit = 0;
  int lowestPrice = prices[0];

  for ( int i = 1; i< prices.size(); ++i) {
    if ( prices[i] < lowestPrice) {
      lowestPrice = prices[i];
    } else {
      const int price = prices[i] - lowestPrice;
      maxProfit += price;
            lowestPrice = prices[i];
    }
  }
  return maxProfit;

}

}



// ---------- maxProfit (single buy/sell) ----------

TEST(BestTimeToSell_SingleBuy_BasicExample) {
    // buy at 1, sell at 6 => profit 5
    int result = BestTimeToSell::maxProfit({7, 1, 5, 3, 6, 4});
    DEBUG_OUT("Input: {7,1,5,3,6,4}, Result: " << result << ", Expected: 5");
    TestBase::assertEqual(5, result);
}

TEST(BestTimeToSell_SingleBuy_DecreasingPrices) {
    // prices only go down, no profit possible
    int result = BestTimeToSell::maxProfit({7, 6, 4, 3, 1});
    DEBUG_OUT("Input: {7,6,4,3,1}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_EmptyArray) {
    int result = BestTimeToSell::maxProfit({});
    DEBUG_OUT("Input: {}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_SingleElement) {
    int result = BestTimeToSell::maxProfit({5});
    DEBUG_OUT("Input: {5}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_TwoElements_Profit) {
    int result = BestTimeToSell::maxProfit({1, 5});
    DEBUG_OUT("Input: {1,5}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_SingleBuy_TwoElements_NoProfit) {
    int result = BestTimeToSell::maxProfit({5, 1});
    DEBUG_OUT("Input: {5,1}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_AllSamePrice) {
    int result = BestTimeToSell::maxProfit({3, 3, 3, 3});
    DEBUG_OUT("Input: {3,3,3,3}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_SingleBuy_IncreasingPrices) {
    // buy at 1, sell at 5 => profit 4
    int result = BestTimeToSell::maxProfit({1, 2, 3, 4, 5});
    DEBUG_OUT("Input: {1,2,3,4,5}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_SingleBuy_MinAtEnd) {
    // min price is at the end, best is buy@1 sell@8
    int result = BestTimeToSell::maxProfit({3, 1, 8, 2, 5, 0});
    DEBUG_OUT("Input: {3,1,8,2,5,0}, Result: " << result << ", Expected: 7");
    TestBase::assertEqual(7, result);
}

TEST(BestTimeToSell_SingleBuy_MaxAtStart) {
    // max price at index 0, best is buy@1 sell@4
    int result = BestTimeToSell::maxProfit({10, 1, 2, 3, 4});
    DEBUG_OUT("Input: {10,1,2,3,4}, Result: " << result << ", Expected: 3");
    TestBase::assertEqual(3, result);
}

TEST(BestTimeToSell_SingleBuy_VShapedPrices) {
    // buy at 1, sell at 10 => profit 9
    int result = BestTimeToSell::maxProfit({8, 5, 3, 1, 6, 10});
    DEBUG_OUT("Input: {8,5,3,1,6,10}, Result: " << result << ", Expected: 9");
    TestBase::assertEqual(9, result);
}

TEST(BestTimeToSell_SingleBuy_LargeSpread) {
    int result = BestTimeToSell::maxProfit({1, 100000});
    DEBUG_OUT("Input: {1,100000}, Result: " << result << ", Expected: 99999");
    TestBase::assertEqual(99999, result);
}

// ---------- maxProfitMultiBuy (multiple buys/sells) ----------

TEST(BestTimeToSell_MultiBuy_BasicExample) {
    // buy@1 sell@5 (+4), buy@3 sell@6 (+3) => 7
    int result = BestTimeToSell::maxProfitMultiBuy({7, 1, 5, 3, 6, 4});
    DEBUG_OUT("Input: {7,1,5,3,6,4}, Result: " << result << ", Expected: 7");
    TestBase::assertEqual(7, result);
}

TEST(BestTimeToSell_MultiBuy_AllIncreasing) {
    // capture every upward tick: 1->2 + 2->3 + 3->4 + 4->5 = 4
    int result = BestTimeToSell::maxProfitMultiBuy({1, 2, 3, 4, 5});
    DEBUG_OUT("Input: {1,2,3,4,5}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_MultiBuy_AllDecreasing) {
    int result = BestTimeToSell::maxProfitMultiBuy({5, 4, 3, 2, 1});
    DEBUG_OUT("Input: {5,4,3,2,1}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_EmptyArray) {
    int result = BestTimeToSell::maxProfitMultiBuy({});
    DEBUG_OUT("Input: {}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_SingleElement) {
    int result = BestTimeToSell::maxProfitMultiBuy({5});
    DEBUG_OUT("Input: {5}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_TwoElements_Profit) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 5});
    DEBUG_OUT("Input: {1,5}, Result: " << result << ", Expected: 4");
    TestBase::assertEqual(4, result);
}

TEST(BestTimeToSell_MultiBuy_TwoElements_NoProfit) {
    int result = BestTimeToSell::maxProfitMultiBuy({5, 1});
    DEBUG_OUT("Input: {5,1}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_AllSamePrice) {
    int result = BestTimeToSell::maxProfitMultiBuy({3, 3, 3, 3});
    DEBUG_OUT("Input: {3,3,3,3}, Result: " << result << ", Expected: 0");
    TestBase::assertEqual(0, result);
}

TEST(BestTimeToSell_MultiBuy_ZigZag) {
    // buy@1 sell@5 (+4), buy@2 sell@8 (+6) => 10
    int result = BestTimeToSell::maxProfitMultiBuy({1, 5, 2, 8});
    DEBUG_OUT("Input: {1,5,2,8}, Result: " << result << ", Expected: 10");
    TestBase::assertEqual(10, result);
}

TEST(BestTimeToSell_MultiBuy_MultipleValleysAndPeaks) {
    // 1->4 (+3), 2->7 (+5), 3->9 (+6) => 14
    int result = BestTimeToSell::maxProfitMultiBuy({1, 4, 2, 7, 3, 9});
    DEBUG_OUT("Input: {1,4,2,7,3,9}, Result: " << result << ", Expected: 14");
    TestBase::assertEqual(14, result);
}

TEST(BestTimeToSell_MultiBuy_LargeSpread) {
    int result = BestTimeToSell::maxProfitMultiBuy({1, 100000});
    DEBUG_OUT("Input: {1,100000}, Result: " << result << ", Expected: 99999");
    TestBase::assertEqual(99999, result);
}

TEST(BestTimeToSell_MultiBuy_SingleTransaction_SameAsSingle) {
    // only one upward move, so multi should match single
    int result = BestTimeToSell::maxProfitMultiBuy({7, 6, 4, 3, 1, 10});
    DEBUG_OUT("Input: {7,6,4,3,1,10}, Result: " << result << ", Expected: 9");
    TestBase::assertEqual(9, result);
}
