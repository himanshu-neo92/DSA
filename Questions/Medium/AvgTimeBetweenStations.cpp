// Problem: Average Time Between Stations
// Track check-in/check-out times of users at stations and compute
// the average travel time between any two stations.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(1) per checkIn/checkOut/getAvg
// Space Complexity: O(n) for tracking active users + route averages
//
// Key concepts:
// - Hash map to track active check-ins by user ID
// - Hash map to track running average per route (station pair)
// - Route key = "stationA;stationB"
// - Duplicate check-in for same ID should be ignored
// - Check-out without check-in is a no-op
// =======================================================

#include "TestBase.h"

namespace AvgTimeBetweenStations {

struct AvgData {
    AvgData()
    : totalTime(0)
    , Instances(0)
    , avg(0.0f) {}

    int totalTime;
    int Instances;
    float avg;
};

class StationData {
public:
    // TODO: implement these methods
    void checkIn(const std::string& stationname, int id, int time);
    void checkOut(const std::string& stationname, int id, int time);
    float getAvg(const std::string& station1, const std::string& station2);

private:
    std::unordered_map<int, std::pair<std::string, int>> trackerMap;
    std::unordered_map<std::string, AvgData> avgMap;
};

void StationData::checkIn(const std::string& stationname, int id, int time) {
    // TODO: implement - record that user `id` checked in at `stationname` at `time`
}

void StationData::checkOut(const std::string& stationname, int id, int time) {
    // TODO: implement - record checkout, update average for the route
}

float StationData::getAvg(const std::string& station1, const std::string& station2) {
    // TODO: implement - return average travel time from station1 to station2
    return 0.0f;
}

}

// ==================== TEST CASES ====================

TEST(AvgTime_SingleTrip) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 20);
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Single trip A->B should average 10");
}

TEST(AvgTime_TwoTrips_SameRoute) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 20);
    sd.checkIn("A", 2, 30);
    sd.checkOut("B", 2, 40);
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Two identical trips should average 10");
}

TEST(AvgTime_TwoTrips_DifferentTimes) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("X", 1, 10);
    sd.checkOut("Y", 1, 20);
    sd.checkIn("X", 2, 20);
    sd.checkOut("Y", 2, 50);
    TestBase::assertEqual(20.0f, sd.getAvg("X", "Y"), "Average of 10 and 30 should be 20");
}

TEST(AvgTime_DifferentRoutes_Independent) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 15);
    sd.checkIn("C", 2, 100);
    sd.checkOut("D", 2, 120);
    TestBase::assertEqual(5.0f, sd.getAvg("A", "B"), "A->B should be 5");
    TestBase::assertEqual(20.0f, sd.getAvg("C", "D"), "C->D should be 20");
}

TEST(AvgTime_UnknownRoute_ReturnsZero) {
    AvgTimeBetweenStations::StationData sd;
    TestBase::assertEqual(0.0f, sd.getAvg("X", "Y"), "Unknown route should return 0");
}

TEST(AvgTime_ReverseRoute_IsDifferent) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 20);
    TestBase::assertEqual(0.0f, sd.getAvg("B", "A"), "Reverse route B->A should return 0");
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Forward route A->B should return 10");
}

TEST(AvgTime_CheckOutWithoutCheckIn_NoEffect) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkOut("B", 99, 50);
    TestBase::assertEqual(0.0f, sd.getAvg("A", "B"), "No data should exist after invalid checkout");
}

TEST(AvgTime_DuplicateCheckIn_Ignored) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    sd.checkIn("Z", 1, 999);
    sd.checkOut("B", 1, 20);
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Duplicate checkIn should be ignored");
}

TEST(AvgTime_MultipleUsers_Concurrent) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("Home", 1, 0);
    sd.checkIn("Home", 2, 5);
    sd.checkIn("Home", 3, 10);
    sd.checkOut("Work", 1, 30);
    sd.checkOut("Work", 2, 25);
    sd.checkOut("Work", 3, 20);
    TestBase::assertEqual(20.0f, sd.getAvg("Home", "Work"), "Average of 30,20,10 should be 20");
}
