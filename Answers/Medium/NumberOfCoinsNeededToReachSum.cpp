// Problem: Minimum Coins Needed to Reach Sum (Coin Change - LeetCode 322)
// Given coins of different denominations and a total amount, find the fewest
// number of coins needed to make up that amount.
// Return -1 if it's not possible.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(amount * coins.size()) - Fill DP table
// Space Complexity: O(amount) - 1D DP array
//
// Key concepts:
// - Bottom-up DP: dp[i] = min coins to make amount i
// - dp[0] = 0, dp[1..amount] = infinity initially
// - For each amount i, try each coin: dp[i] = min(dp[i], 1 + dp[i - coin])
// =======================================================

#include "TestBase.h"
#include <climits>

namespace NumberOfCoinsNeededToReachSum {

// ========== Solution ==========
int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = std::min(dp[i], 1 + dp[i - coin]);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// ========== Tests ==========

TEST(CoinChange_Basic) {
    TestBase::assertEqual(2, coinChange({1, 5, 10, 25}, 30));
}

TEST(CoinChange_LeetCode1) {
    TestBase::assertEqual(3, coinChange({1, 2, 5}, 11));
}

TEST(CoinChange_Impossible) {
    TestBase::assertEqual(-1, coinChange({2}, 3));
}

TEST(CoinChange_Zero) {
    TestBase::assertEqual(0, coinChange({1, 2, 5}, 0));
}

TEST(CoinChange_SingleCoin) {
    TestBase::assertEqual(5, coinChange({1}, 5));
}

TEST(CoinChange_ExactCoin) {
    TestBase::assertEqual(1, coinChange({1, 5, 10}, 10));
}

TEST(CoinChange_LargeAmount) {
    TestBase::assertEqual(4, coinChange({1, 5, 10, 25}, 100));
}

TEST(CoinChange_NoCoinsFit) {
    TestBase::assertEqual(-1, coinChange({5, 10}, 3));
}

TEST(CoinChange_OneCoin) {
    TestBase::assertEqual(1, coinChange({1}, 1));
}

} // namespace NumberOfCoinsNeededToReachSum
