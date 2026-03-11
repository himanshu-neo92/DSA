// Problem: Average Time Between Stations
// Track passenger check-in/check-out at stations and compute average
// travel time between any two stations.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(1) per checkIn, checkOut, and getAvg operation
// Space Complexity: O(n) - maps for active travelers and route averages
//
// Key concepts:
// - Hash map for active check-ins keyed by passenger ID
// - Running average maintained per route (source;destination)
// =======================================================

#include "TestBase.h"

namespace AvgTimeBetweenStations {

  struct AvgData{
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
    void checkIn(const std::string& stationname, int id, int time);
    void checkOut(const std::string& stationname, int id, int time);
    float getAvg(const std::string& station1, const std::string& station2);


    private:
    std::unordered_map<int, std::pair<std::string, int>> trackerMap;
    std::unordered_map<std::string, AvgData> avgMap;

  };

  void StationData::checkIn(const std::string& stationname, int id, int time) {
    if (trackerMap.count(id)) {
      // invalid;
      return;
    }

    trackerMap[id] = {stationname, time};
  }

  void StationData::checkOut(const std::string& stationname, int id, int time) {

    if (!trackerMap.count(id)) {
      // invalid;
      return;
    }

    std::pair<std::string, int> data = trackerMap[id];

    std::string avgName = data.first + (";");
    avgName += stationname;

    if (avgMap.count(avgName)) {
      AvgData& avg = avgMap[avgName];
      avg.totalTime += time - data.second;
      avg.Instances++;

      avg.avg = avg.totalTime / avg.Instances;

    } else {
       AvgData avg;
      avg.totalTime += time - data.second;
      avg.Instances++;

      avg.avg = avg.totalTime / avg.Instances;
      avgMap[avgName] =avg;
    }

    trackerMap.erase(id);
  }

    float StationData::getAvg(const std::string& station1, const std::string& station2) {
    std::string avgName = station1 + ";";
    avgName += station2;

        if (avgMap.count(avgName)) {
          return avgMap[avgName].avg;
        }

        return 0.0f;
    }

}

// ==================== TEST CASES ====================

TEST(AvgTime_SingleTrip) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 20);
    // Travel time = 20 - 10 = 10, average of one trip = 10.0
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Single trip A->B should average 10");
}

TEST(AvgTime_TwoTrips_SameRoute) {
    AvgTimeBetweenStations::StationData sd;
    // Trip 1: travel time = 20 - 10 = 10
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 20);
    // Trip 2: travel time = 40 - 30 = 10
    sd.checkIn("A", 2, 30);
    sd.checkOut("B", 2, 40);
    // Average = (10 + 10) / 2 = 10.0
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Two identical trips should average 10");
}

TEST(AvgTime_TwoTrips_DifferentTimes) {
    AvgTimeBetweenStations::StationData sd;
    // Trip 1: travel time = 20 - 10 = 10
    sd.checkIn("X", 1, 10);
    sd.checkOut("Y", 1, 20);
    // Trip 2: travel time = 50 - 20 = 30
    sd.checkIn("X", 2, 20);
    sd.checkOut("Y", 2, 50);
    // Average = (10 + 30) / 2 = 20.0
    TestBase::assertEqual(20.0f, sd.getAvg("X", "Y"), "Average of 10 and 30 should be 20");
}

TEST(AvgTime_DifferentRoutes_Independent) {
    AvgTimeBetweenStations::StationData sd;
    // Route A->B: travel time = 5
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 15);
    // Route C->D: travel time = 20
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
    // A->B trip
    sd.checkIn("A", 1, 10);
    sd.checkOut("B", 1, 20);
    // B->A is a different route and should not have data
    TestBase::assertEqual(0.0f, sd.getAvg("B", "A"), "Reverse route B->A should return 0");
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Forward route A->B should return 10");
}

TEST(AvgTime_CheckOutWithoutCheckIn_NoEffect) {
    AvgTimeBetweenStations::StationData sd;
    // checkOut for a user who never checked in should be a no-op
    sd.checkOut("B", 99, 50);
    TestBase::assertEqual(0.0f, sd.getAvg("A", "B"), "No data should exist after invalid checkout");
}

TEST(AvgTime_DuplicateCheckIn_Ignored) {
    AvgTimeBetweenStations::StationData sd;
    sd.checkIn("A", 1, 10);
    // Second checkIn for same id should be ignored
    sd.checkIn("Z", 1, 999);
    sd.checkOut("B", 1, 20);
    // Should use original checkIn at station A, time 10
    TestBase::assertEqual(10.0f, sd.getAvg("A", "B"), "Duplicate checkIn should be ignored");
}

TEST(AvgTime_MultipleUsers_Concurrent) {
    AvgTimeBetweenStations::StationData sd;
    // Multiple users traveling concurrently on the same route
    sd.checkIn("Home", 1, 0);
    sd.checkIn("Home", 2, 5);
    sd.checkIn("Home", 3, 10);
    sd.checkOut("Work", 1, 30);  // travel = 30
    sd.checkOut("Work", 2, 25);  // travel = 20
    sd.checkOut("Work", 3, 20);  // travel = 10
    // Average = (30 + 20 + 10) / 3 = 20.0
    TestBase::assertEqual(20.0f, sd.getAvg("Home", "Work"), "Average of 30,20,10 should be 20");
}
