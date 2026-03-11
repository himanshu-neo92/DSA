/*
Problem: Social Network Friend Recommendation
Recommend friends-of-friends who are not already direct friends.

Approach:
- Use hash maps and sets to store user connections
- For each friend of the user, iterate over their friends
- Collect friends-of-friends not already directly connected and not self

==================== PERFORMANCE ====================
Time Complexity:  O(F * G) where F = friends of user, G = avg friends per friend
Space Complexity: O(R) where R = number of recommendations
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace FriendRecommendation {

std::vector<int> recommendFriends(int userId,
    std::unordered_map<int, std::unordered_set<int>>& friends) {
    std::unordered_set<int> directFriends = friends[userId];
    std::unordered_set<int> recommendations;
    for (int friendId : directFriends) {
        for (int fof : friends[friendId]) {
            if (fof != userId && !directFriends.count(fof))
                recommendations.insert(fof);
        }
    }
    return std::vector<int>(recommendations.begin(), recommendations.end());
}

// ========== Tests ==========

TEST(FriendRec_BasicRecommendation) {
    std::unordered_map<int, std::unordered_set<int>> friends;
    friends[1] = {2, 4};
    friends[2] = {1, 3};
    friends[3] = {2};
    friends[4] = {1};

    auto recs = recommendFriends(1, friends);
    std::unordered_set<int> recSet(recs.begin(), recs.end());
    TestBase::assertTrue(recSet.count(3) > 0, "Should recommend 3 (friend of 2)");
    TestBase::assertTrue(recSet.count(1) == 0, "Should not recommend self");
    TestBase::assertTrue(recSet.count(2) == 0, "Should not recommend direct friend 2");
    TestBase::assertTrue(recSet.count(4) == 0, "Should not recommend direct friend 4");
}

TEST(FriendRec_NoRecommendations) {
    std::unordered_map<int, std::unordered_set<int>> friends;
    friends[1] = {2};
    friends[2] = {1};

    auto recs = recommendFriends(1, friends);
    TestBase::assertEqual(0, (int)recs.size());
}

TEST(FriendRec_MultipleRecommendations) {
    std::unordered_map<int, std::unordered_set<int>> friends;
    friends[1] = {2, 4};
    friends[2] = {1, 3};
    friends[3] = {2, 5};
    friends[4] = {1, 5};
    friends[5] = {3, 4};

    auto recs = recommendFriends(1, friends);
    std::unordered_set<int> recSet(recs.begin(), recs.end());
    TestBase::assertTrue(recSet.count(3) > 0, "Should recommend 3");
    TestBase::assertTrue(recSet.count(5) > 0, "Should recommend 5");
}

TEST(FriendRec_NoFriends) {
    std::unordered_map<int, std::unordered_set<int>> friends;
    friends[1] = {};

    auto recs = recommendFriends(1, friends);
    TestBase::assertEqual(0, (int)recs.size());
}

TEST(FriendRec_AllAlreadyFriends) {
    std::unordered_map<int, std::unordered_set<int>> friends;
    friends[1] = {2, 3};
    friends[2] = {1, 3};
    friends[3] = {1, 2};

    auto recs = recommendFriends(1, friends);
    TestBase::assertEqual(0, (int)recs.size());
}

} // namespace FriendRecommendation
