// Problem: Car Fleet (LeetCode 853)
//
// There are n cars going to the same destination along a one-lane road.
// The destination is at position `target` miles away.
//
// You are given two integer arrays position[] and speed[], both of length n,
// where position[i] is the starting position of the ith car and speed[i] is
// the speed of the ith car (in miles per hour).
//
// A car can never pass another car ahead of it, but it can catch up and then
// travel at the same speed as the car ahead. A group of cars traveling at the
// same speed is called a "car fleet".
//
// A single car is also a car fleet.
//
// Return the number of car fleets that will arrive at the destination.
//
// Approach:
//   1. Pair each car's (position, speed) and sort by position descending.
//   2. Compute the time each car would take to reach the target:
//        time = (target - position) / speed
//   3. Iterate through the sorted cars. If a car's time is greater than the
//      current fleet's time, it cannot merge — it starts a new fleet.
//      Otherwise it merges into the fleet ahead (its time is <= the fleet's).
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) — sorting dominates
// Space Complexity: O(n) — for the (position, speed) pairs
//
// Key concepts: greedy via sorting by position descending,
// then comparing arrival times to merge fleets.
// =======================================================

#include "TestBase.h"
#include <vector>
#include <algorithm>

namespace CarFleetToReachEnd {

int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
    int n = position.size();
    if (n == 0) return 0;

    std::vector<std::pair<int, int>> cars(n);
    for (int i = 0; i < n; ++i) {
        cars[i] = {position[i], speed[i]};
    }

    // sort by position descending (closest to target first)
    std::sort(cars.begin(), cars.end(), [](auto& a, auto& b) {
        return a.first > b.first;
    });

    int fleets = 0;
    double slowest = -1.0;

    for (auto& [pos, spd] : cars) {
        double time = static_cast<double>(target - pos) / spd;
        if (time > slowest) {
            ++fleets;
            slowest = time;
        }
    }

    return fleets;
}

// ========== Tests ==========

// Example 1: target=12, position=[10,8,0,5,3], speed=[2,4,1,1,3]
//   Car at 10 → time = (12-10)/2 = 1.0
//   Car at  8 → time = (12-8)/4  = 1.0  → merges with car at 10
//   Car at  5 → time = (12-5)/1  = 7.0  → new fleet
//   Car at  3 → time = (12-3)/3  = 3.0  → merges with car at 5 (blocked behind)
//   Car at  0 → time = (12-0)/1  = 12.0 → new fleet
// Answer: 3 fleets
TEST(CarFleet_Example1) {
    int target = 12;
    std::vector<int> position = {10, 8, 0, 5, 3};
    std::vector<int> speed    = {2, 4, 1, 1, 3};

    TestBase::assertEqual(3, carFleet(target, position, speed));
}

// Example 2: target=10, position=[3], speed=[3]
// Only one car → 1 fleet
TEST(CarFleet_SingleCar) {
    int target = 10;
    std::vector<int> position = {3};
    std::vector<int> speed    = {3};

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

// Example 3: target=100, position=[0,2,4], speed=[4,2,1]
//   Car at 4 → time = 96/1 = 96
//   Car at 2 → time = 98/2 = 49  → merges with car at 4 (blocked behind, 49 < 96)
//   Car at 0 → time = 100/4 = 25 → merges too (25 < 96)
// Answer: 1 fleet
TEST(CarFleet_AllMerge) {
    int target = 100;
    std::vector<int> position = {0, 2, 4};
    std::vector<int> speed    = {4, 2, 1};

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

// All cars at different positions with same speed → no merging, each is its own fleet
TEST(CarFleet_SameSpeed) {
    int target = 10;
    std::vector<int> position = {0, 2, 4, 6};
    std::vector<int> speed    = {1, 1, 1, 1};

    TestBase::assertEqual(4, carFleet(target, position, speed));
}

// Two cars at different positions: faster car behind catches up → 1 fleet
TEST(CarFleet_TwoCars_Merge) {
    int target = 10;
    std::vector<int> position = {0, 5};
    std::vector<int> speed    = {3, 1};
    // Car at 5 → time = 5/1 = 5.0
    // Car at 0 → time = 10/3 ≈ 3.33 → merges (3.33 < 5.0)

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

// Two cars: slower car behind, never catches up → 2 fleets
TEST(CarFleet_TwoCars_NoMerge) {
    int target = 10;
    std::vector<int> position = {0, 5};
    std::vector<int> speed    = {1, 3};
    // Car at 5 → time = 5/3 ≈ 1.67
    // Car at 0 → time = 10/1 = 10.0 → new fleet (10.0 > 1.67)

    TestBase::assertEqual(2, carFleet(target, position, speed));
}

// Edge: no cars → 0 fleets
TEST(CarFleet_Empty) {
    int target = 10;
    std::vector<int> position = {};
    std::vector<int> speed    = {};

    TestBase::assertEqual(0, carFleet(target, position, speed));
}

// Cars already at the target
TEST(CarFleet_AtTarget) {
    int target = 5;
    std::vector<int> position = {5, 5, 5};
    std::vector<int> speed    = {1, 2, 3};
    // All times are 0 → they all form 1 fleet

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

} // namespace CarFleetToReachEnd
