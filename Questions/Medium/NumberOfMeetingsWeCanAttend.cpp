// Problem: Maximum Number of Meetings We Can Attend
// Given a list of meetings with start and end times, find the maximum number
// of non-overlapping meetings one person can attend.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) - Sort by end time
// Space Complexity: O(1) - In-place sort
//
// Key concepts:
// - Greedy: always pick the meeting that ends earliest
// - Sort meetings by end time
// - Track when the last attended meeting ended
// =======================================================

#include "TestBase.h"
#include <algorithm>

namespace NumberOfMeetingsWeCanAttend {

// ========== Solution ==========
int maxMeetings(std::vector<std::pair<int,int>>& meetings) {
    // TODO: implement your solution here
    return 0;
}

// ========== Tests ==========

TEST(MaxMeetings_Basic) {
    std::vector<std::pair<int,int>> m = {{1,3},{2,4},{3,5}};
    TestBase::assertEqual(2, maxMeetings(m));
}

TEST(MaxMeetings_NoOverlap) {
    std::vector<std::pair<int,int>> m = {{1,2},{3,4},{5,6}};
    TestBase::assertEqual(3, maxMeetings(m));
}

TEST(MaxMeetings_AllOverlap) {
    std::vector<std::pair<int,int>> m = {{1,10},{2,9},{3,8}};
    TestBase::assertEqual(1, maxMeetings(m));
}

TEST(MaxMeetings_Empty) {
    std::vector<std::pair<int,int>> m = {};
    TestBase::assertEqual(0, maxMeetings(m));
}

TEST(MaxMeetings_Single) {
    std::vector<std::pair<int,int>> m = {{5,10}};
    TestBase::assertEqual(1, maxMeetings(m));
}

TEST(MaxMeetings_BackToBack) {
    std::vector<std::pair<int,int>> m = {{1,2},{2,3},{3,4},{4,5}};
    TestBase::assertEqual(4, maxMeetings(m));
}

TEST(MaxMeetings_Complex) {
    std::vector<std::pair<int,int>> m = {{0,6},{1,4},{3,5},{3,8},{4,7},{5,9},{6,10},{8,11}};
    TestBase::assertEqual(3, maxMeetings(m));
}

} // namespace NumberOfMeetingsWeCanAttend
