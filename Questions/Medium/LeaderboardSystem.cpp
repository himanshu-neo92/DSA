/*
Problem: Leaderboard System (Ranking Users by Score)
Maintain a real-time leaderboard with add/update score and retrieve top-k users.

Approach:
- Use a hash map for user scores
- Use a multiset of (score, userId) pairs for O(log n) ranking
- On score update, remove old entry and insert new one

==================== PERFORMANCE ====================
Time Complexity:  O(log n) per addScore, O(k) for top-k
Space Complexity: O(n) where n = number of users
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <set>
#include <vector>

namespace LeaderboardSystem {

class Leaderboard {
public:
    // TODO: implement addScore and top
    void addScore(int userId, int score) {}

    std::vector<int> top(int k) {
        return {};
    }

private:
    std::unordered_map<int, int> userScores;
    std::multiset<std::pair<int, int>> scoreSet;
};

// ========== Tests ==========

TEST(Leaderboard_BasicTopK) {
    Leaderboard lb;
    lb.addScore(1, 100);
    lb.addScore(2, 200);
    lb.addScore(3, 150);

    auto topUsers = lb.top(2);
    TestBase::assertEqual(2, (int)topUsers.size());
    TestBase::assertEqual(2, topUsers[0]);
    TestBase::assertEqual(3, topUsers[1]);
}

TEST(Leaderboard_AccumulateScores) {
    Leaderboard lb;
    lb.addScore(1, 50);
    lb.addScore(1, 60);

    auto topUsers = lb.top(1);
    TestBase::assertEqual(1, topUsers[0]);
}

TEST(Leaderboard_TopKMoreThanUsers) {
    Leaderboard lb;
    lb.addScore(1, 10);

    auto topUsers = lb.top(5);
    TestBase::assertEqual(1, (int)topUsers.size());
}

TEST(Leaderboard_OrderAfterUpdate) {
    Leaderboard lb;
    lb.addScore(1, 100);
    lb.addScore(2, 50);
    lb.addScore(2, 200);

    auto topUsers = lb.top(2);
    TestBase::assertEqual(2, topUsers[0]);
    TestBase::assertEqual(1, topUsers[1]);
}

TEST(Leaderboard_SingleUser) {
    Leaderboard lb;
    lb.addScore(42, 999);

    auto topUsers = lb.top(1);
    TestBase::assertEqual(1, (int)topUsers.size());
    TestBase::assertEqual(42, topUsers[0]);
}

TEST(Leaderboard_MultipleUsers) {
    Leaderboard lb;
    lb.addScore(1, 10);
    lb.addScore(2, 20);
    lb.addScore(3, 30);
    lb.addScore(4, 40);
    lb.addScore(5, 50);

    auto topUsers = lb.top(3);
    TestBase::assertEqual(3, (int)topUsers.size());
    TestBase::assertEqual(5, topUsers[0]);
    TestBase::assertEqual(4, topUsers[1]);
    TestBase::assertEqual(3, topUsers[2]);
}

} // namespace LeaderboardSystem
