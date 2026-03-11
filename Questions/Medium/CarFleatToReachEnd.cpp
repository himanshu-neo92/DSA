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
// Time:  O(n log n) — sorting
// Space: O(n)

#include "TestBase.h"
#include <vector>
#include <algorithm>

namespace CarFleetToReachEnd {

// ========== Solution ==========
int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
    // TODO: implement your solution here
    return -1;
}

// ========== Tests ==========

TEST(CarFleet_Example1) {
    int target = 12;
    std::vector<int> position = {10, 8, 0, 5, 3};
    std::vector<int> speed    = {2, 4, 1, 1, 3};

    TestBase::assertEqual(3, carFleet(target, position, speed));
}

TEST(CarFleet_SingleCar) {
    int target = 10;
    std::vector<int> position = {3};
    std::vector<int> speed    = {3};

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

TEST(CarFleet_AllMerge) {
    int target = 100;
    std::vector<int> position = {0, 2, 4};
    std::vector<int> speed    = {4, 2, 1};

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

TEST(CarFleet_SameSpeed) {
    int target = 10;
    std::vector<int> position = {0, 2, 4, 6};
    std::vector<int> speed    = {1, 1, 1, 1};

    TestBase::assertEqual(4, carFleet(target, position, speed));
}

TEST(CarFleet_TwoCars_Merge) {
    int target = 10;
    std::vector<int> position = {0, 5};
    std::vector<int> speed    = {3, 1};

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

TEST(CarFleet_TwoCars_NoMerge) {
    int target = 10;
    std::vector<int> position = {0, 5};
    std::vector<int> speed    = {1, 3};

    TestBase::assertEqual(2, carFleet(target, position, speed));
}

TEST(CarFleet_Empty) {
    int target = 10;
    std::vector<int> position = {};
    std::vector<int> speed    = {};

    TestBase::assertEqual(0, carFleet(target, position, speed));
}

TEST(CarFleet_AtTarget) {
    int target = 5;
    std::vector<int> position = {5, 5, 5};
    std::vector<int> speed    = {1, 2, 3};

    TestBase::assertEqual(1, carFleet(target, position, speed));
}

} // namespace CarFleetToReachEnd
