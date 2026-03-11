/*
Problem: Sliding Window API Rate Limiter
Design a rate limiter to allow up to N requests per user in a sliding
window of T seconds.

Approach:
- Use a deque to store timestamps for each user
- Remove timestamps outside the window
- Allow request if the number of timestamps within the window is less than N

==================== PERFORMANCE ====================
Time Complexity:  O(1) amortized per request (each timestamp added/removed once)
Space Complexity: O(U * N) where U = users, N = max requests per window
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <deque>
#include <string>

namespace RateLimiter {

class RateLimiterSystem {
public:
    // TODO: implement constructor and allowRequest
    RateLimiterSystem(int maxRequests, int windowSeconds)
        : maxRequests(maxRequests), windowSeconds(windowSeconds) {}

    bool allowRequest(const std::string& userId, long long timestamp) {
        return false;
    }

private:
    int maxRequests;
    int windowSeconds;
    std::unordered_map<std::string, std::deque<long long>> userRequests;
};

// ========== Tests ==========

TEST(RateLimiter_AllowWithinLimit) {
    RateLimiterSystem rl(3, 10);
    TestBase::assertTrue(rl.allowRequest("user1", 1), "First request allowed");
    TestBase::assertTrue(rl.allowRequest("user1", 2), "Second request allowed");
    TestBase::assertTrue(rl.allowRequest("user1", 3), "Third request allowed");
}

TEST(RateLimiter_BlockOverLimit) {
    RateLimiterSystem rl(2, 10);
    TestBase::assertTrue(rl.allowRequest("user1", 1), "First allowed");
    TestBase::assertTrue(rl.allowRequest("user1", 2), "Second allowed");
    TestBase::assertFalse(rl.allowRequest("user1", 3), "Third blocked");
}

TEST(RateLimiter_WindowExpiry) {
    RateLimiterSystem rl(2, 5);
    TestBase::assertTrue(rl.allowRequest("user1", 1), "t=1 allowed");
    TestBase::assertTrue(rl.allowRequest("user1", 2), "t=2 allowed");
    TestBase::assertFalse(rl.allowRequest("user1", 3), "t=3 blocked");
    TestBase::assertTrue(rl.allowRequest("user1", 6), "t=6 allowed (t=1 expired)");
}

TEST(RateLimiter_DifferentUsers) {
    RateLimiterSystem rl(1, 10);
    TestBase::assertTrue(rl.allowRequest("user1", 1), "user1 allowed");
    TestBase::assertFalse(rl.allowRequest("user1", 2), "user1 blocked");
    TestBase::assertTrue(rl.allowRequest("user2", 2), "user2 allowed (separate limit)");
}

TEST(RateLimiter_BurstThenWait) {
    RateLimiterSystem rl(3, 5);
    TestBase::assertTrue(rl.allowRequest("u", 1), "1st");
    TestBase::assertTrue(rl.allowRequest("u", 1), "2nd same time");
    TestBase::assertTrue(rl.allowRequest("u", 1), "3rd same time");
    TestBase::assertFalse(rl.allowRequest("u", 1), "4th blocked");
    TestBase::assertTrue(rl.allowRequest("u", 6), "After window reset");
}

TEST(RateLimiter_ExactWindowBoundary) {
    RateLimiterSystem rl(1, 5);
    TestBase::assertTrue(rl.allowRequest("u", 0), "t=0 allowed");
    TestBase::assertFalse(rl.allowRequest("u", 4), "t=4 blocked (within window)");
    TestBase::assertTrue(rl.allowRequest("u", 5), "t=5 allowed (window expired)");
}

} // namespace RateLimiter
