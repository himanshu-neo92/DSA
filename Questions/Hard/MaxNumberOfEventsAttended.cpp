// Problem: Maximum Number of Events Attended (LeetCode 1353)
// Given an array of events where events[i] = [startDay, endDay],
// you can attend at most one event per day. Return the maximum number
// of events you can attend.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) - Sort + priority queue operations
// Space Complexity: O(n) - Priority queue
//
// Key concepts:
// - Sort events by start day
// - Use a min-heap of end days for active events
// - For each day, add newly available events, remove expired ones,
//   attend the one ending soonest (greedy)
// =======================================================

#include "TestBase.h"
#include <algorithm>
#include <queue>

namespace MaxNumberOfEventsAttended {

// ========== Solution ==========
int maxEvents(std::vector<std::vector<int>>& events) {
    // TODO: implement your solution here
    return 0;
}

// ========== Tests ==========

TEST(MaxEvents_Basic) {
    std::vector<std::vector<int>> events = {{1,2},{2,3},{3,4}};
    TestBase::assertEqual(3, maxEvents(events));
}

TEST(MaxEvents_Overlapping) {
    std::vector<std::vector<int>> events = {{1,2},{2,3},{3,4},{1,2}};
    TestBase::assertEqual(4, maxEvents(events));
}

TEST(MaxEvents_AllSameDay) {
    std::vector<std::vector<int>> events = {{1,1},{1,1},{1,1}};
    TestBase::assertEqual(1, maxEvents(events));
}

TEST(MaxEvents_Single) {
    std::vector<std::vector<int>> events = {{1,5}};
    TestBase::assertEqual(1, maxEvents(events));
}

TEST(MaxEvents_NoOverlap) {
    std::vector<std::vector<int>> events = {{1,1},{2,2},{3,3}};
    TestBase::assertEqual(3, maxEvents(events));
}

TEST(MaxEvents_LeetCodeExample) {
    std::vector<std::vector<int>> events = {{1,4},{4,4},{2,2},{3,4},{1,1}};
    TestBase::assertEqual(4, maxEvents(events));
}

TEST(MaxEvents_Empty) {
    std::vector<std::vector<int>> events = {};
    TestBase::assertEqual(0, maxEvents(events));
}

} // namespace MaxNumberOfEventsAttended
