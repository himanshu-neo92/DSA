// Problem: Meeting Rooms Needed (LeetCode 253)
// Given a list of meeting time intervals, find the minimum number of
// conference rooms required.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) - Sort start/end times
// Space Complexity: O(n) - Separate start/end arrays
//
// Key concepts:
// - Separate start and end times, sort independently
// - Sweep through: each start needs a room, each end frees a room
// - Track maximum concurrent meetings
// =======================================================

#include "TestBase.h"
#include <algorithm>

namespace MeetingRoomsNeeded {

// ========== Solution ==========
int minMeetingRooms(std::vector<std::pair<int,int>>& intervals) {
    if (intervals.empty()) return 0;

    std::vector<int> starts, ends;
    for (const auto& p : intervals) {
        starts.push_back(p.first);
        ends.push_back(p.second);
    }

    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());

    int rooms = 0, maxRooms = 0;
    int s = 0, e = 0;
    int n = intervals.size();

    while (s < n) {
        if (starts[s] < ends[e]) {
            rooms++;
            maxRooms = std::max(maxRooms, rooms);
            s++;
        } else {
            rooms--;
            e++;
        }
    }

    return maxRooms;
}

// ========== Tests ==========

TEST(MeetingRooms_Basic) {
    std::vector<std::pair<int,int>> m = {{0,30},{5,10},{15,20}};
    TestBase::assertEqual(2, minMeetingRooms(m));
}

TEST(MeetingRooms_NoOverlap) {
    std::vector<std::pair<int,int>> m = {{1,5},{6,10},{11,15}};
    TestBase::assertEqual(1, minMeetingRooms(m));
}

TEST(MeetingRooms_AllOverlap) {
    std::vector<std::pair<int,int>> m = {{1,10},{2,9},{3,8},{4,7}};
    TestBase::assertEqual(4, minMeetingRooms(m));
}

TEST(MeetingRooms_Empty) {
    std::vector<std::pair<int,int>> m = {};
    TestBase::assertEqual(0, minMeetingRooms(m));
}

TEST(MeetingRooms_Single) {
    std::vector<std::pair<int,int>> m = {{1,5}};
    TestBase::assertEqual(1, minMeetingRooms(m));
}

TEST(MeetingRooms_Sequential) {
    std::vector<std::pair<int,int>> m = {{1,2},{2,3},{3,4}};
    TestBase::assertEqual(1, minMeetingRooms(m));
}

TEST(MeetingRooms_ThreeOverlap) {
    std::vector<std::pair<int,int>> m = {{0,5},{1,6},{2,7},{8,10}};
    TestBase::assertEqual(3, minMeetingRooms(m));
}

} // namespace MeetingRoomsNeeded
