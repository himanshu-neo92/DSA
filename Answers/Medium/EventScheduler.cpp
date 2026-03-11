/*
Problem: Event Scheduler (Interval Overlap Detection)
Schedule events and detect if a new event overlaps with existing ones.

Approach:
- Use a balanced BST (std::set) to store intervals sorted by end time
- Before inserting, check for overlaps using lower_bound
- Insert only if no overlap is detected

==================== PERFORMANCE ====================
Time Complexity:  O(log n) per schedule operation
Space Complexity: O(n) for storing intervals
=======================================================
*/

#include "TestBase.h"
#include <set>

namespace EventScheduler {

struct Interval {
    int start, end;
    bool operator<(const Interval& other) const {
        return end <= other.start;
    }
};

class Scheduler {
public:
    bool schedule(int start, int end) {
        Interval newInterval{start, end};
        auto it = intervals.lower_bound(newInterval);
        if (it != intervals.end() && it->start < end) return false;
        if (it != intervals.begin()) {
            --it;
            if (it->end > start) return false;
        }
        intervals.insert(newInterval);
        return true;
    }

private:
    std::set<Interval> intervals;
};

// ========== Tests ==========

TEST(EventScheduler_NoOverlap) {
    Scheduler s;
    TestBase::assertTrue(s.schedule(1, 3), "First event always ok");
    TestBase::assertTrue(s.schedule(5, 7), "No overlap");
    TestBase::assertTrue(s.schedule(3, 5), "Adjacent, no overlap");
}

TEST(EventScheduler_Overlap) {
    Scheduler s;
    TestBase::assertTrue(s.schedule(1, 5), "First event");
    TestBase::assertFalse(s.schedule(3, 7), "Overlaps with [1,5)");
}

TEST(EventScheduler_ContainedOverlap) {
    Scheduler s;
    TestBase::assertTrue(s.schedule(1, 10), "Wide event");
    TestBase::assertFalse(s.schedule(3, 5), "Contained within [1,10)");
}

TEST(EventScheduler_ExactSameEvent) {
    Scheduler s;
    TestBase::assertTrue(s.schedule(1, 5), "First booking");
    TestBase::assertFalse(s.schedule(1, 5), "Exact duplicate");
}

TEST(EventScheduler_AdjacentEvents) {
    Scheduler s;
    TestBase::assertTrue(s.schedule(1, 3), "First");
    TestBase::assertTrue(s.schedule(3, 5), "[3,5) starts where [1,3) ends");
    TestBase::assertTrue(s.schedule(5, 7), "[5,7) starts where [3,5) ends");
}

TEST(EventScheduler_MultipleNonOverlapping) {
    Scheduler s;
    TestBase::assertTrue(s.schedule(10, 20), "Event 1");
    TestBase::assertTrue(s.schedule(1, 5), "Event 2 before");
    TestBase::assertTrue(s.schedule(25, 30), "Event 3 after");
    TestBase::assertFalse(s.schedule(15, 25), "Overlaps event 1");
}

} // namespace EventScheduler
