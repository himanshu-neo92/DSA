/*
Write a function to record travel from source to destination.
Write a function with source and destination as the param, print all paths from given src to dest.

==================== PERFORMANCE ====================
Time Complexity:  O(V! / (V-P)!) where V = vertices, P = path length
Space Complexity: O(V + E) for adjacency list + O(V) for recursion stack

Key concepts:
- Graph representation using adjacency list
- DFS with backtracking to find all paths
- Visited set to avoid cycles
- Backtrack by removing from visited after exploring
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <unordered_set>
#include <sstream>

namespace AirPath {

class Paths {
private:
  std::unordered_map<std::string, std::vector<std::string>> adjList;

  void dfs(const std::string& current, const std::string& dest,
           std::vector<std::string>& path, std::unordered_set<std::string>& visited,
           std::vector<std::vector<std::string>>& allPaths) {
    // TODO: implement DFS with backtracking
  }

public:
  void travel(const std::string& src, const std::string& dest) {
    adjList[src].push_back(dest);
  }

  std::vector<std::vector<std::string>> getAllPaths(const std::string& src, const std::string& dest) {
    // TODO: implement - find all paths from src to dest using DFS
    return {};
  }

  void printAllPathsBetweenAandB(const std::string& src, const std::string& dest) {
    auto paths = getAllPaths(src, dest);

    if (paths.empty()) {
      std::cout << "No paths from " << src << " to " << dest << '\n';
      return;
    }

    std::cout << "All paths from " << src << " to " << dest << ":" << '\n';
    for (const auto& path : paths) {
      for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
      }
      std::cout << '\n';
    }
  }

  std::string pathToString(const std::vector<std::string>& path) {
    std::ostringstream oss;
    for (size_t i = 0; i < path.size(); i++) {
      oss << path[i];
      if (i < path.size() - 1) oss << " -> ";
    }
    return oss.str();
  }

  void clear() {
    adjList.clear();
  }

  bool hasDirectFlight(const std::string& src, const std::string& dest) {
    if (adjList.find(src) == adjList.end()) return false;
    for (const auto& neighbor : adjList[src]) {
      if (neighbor == dest) return true;
    }
    return false;
  }

  std::vector<std::string> getDestinations(const std::string& src) {
    if (adjList.find(src) == adjList.end()) {
      return {};
    }
    return adjList[src];
  }
};

TEST(AirPath_BasicTravel) {
  Paths paths;
  paths.travel("NYC", "LA");
  paths.travel("NYC", "Chicago");
  paths.travel("Chicago", "LA");

  TestBase::assertTrue(paths.hasDirectFlight("NYC", "LA"), "NYC -> LA direct flight exists");
  TestBase::assertTrue(paths.hasDirectFlight("NYC", "Chicago"), "NYC -> Chicago direct flight exists");
  TestBase::assertTrue(paths.hasDirectFlight("Chicago", "LA"), "Chicago -> LA direct flight exists");
  TestBase::assertFalse(paths.hasDirectFlight("LA", "NYC"), "LA -> NYC direct flight does not exist");
}

TEST(AirPath_SinglePath) {
  Paths paths;
  paths.travel("A", "B");
  paths.travel("B", "C");

  auto allPaths = paths.getAllPaths("A", "C");
  TestBase::assertEqual((int)allPaths.size(), 1, "Should have exactly 1 path");

  std::vector<std::string> expected = {"A", "B", "C"};
  TestBase::assertTrue(allPaths[0] == expected, "Path should be A -> B -> C");
}

TEST(AirPath_MultiplePaths) {
  Paths paths;
  paths.travel("NYC", "LA");
  paths.travel("NYC", "Chicago");
  paths.travel("Chicago", "LA");

  auto allPaths = paths.getAllPaths("NYC", "LA");
  TestBase::assertEqual((int)allPaths.size(), 2, "Should have 2 paths from NYC to LA");

  std::vector<std::string> directPath = {"NYC", "LA"};
  std::vector<std::string> viaChicago = {"NYC", "Chicago", "LA"};

  bool foundDirect = false, foundViaChicago = false;
  for (const auto& path : allPaths) {
    if (path == directPath) foundDirect = true;
    if (path == viaChicago) foundViaChicago = true;
  }

  TestBase::assertTrue(foundDirect, "Should find direct NYC -> LA path");
  TestBase::assertTrue(foundViaChicago, "Should find NYC -> Chicago -> LA path");
}

TEST(AirPath_NoPath) {
  Paths paths;
  paths.travel("A", "B");
  paths.travel("C", "D");

  auto allPaths = paths.getAllPaths("A", "D");
  TestBase::assertEqual((int)allPaths.size(), 0, "Should have no paths from A to D");
}

TEST(AirPath_ComplexGraph) {
  Paths paths;
  paths.travel("A", "B");
  paths.travel("A", "C");
  paths.travel("B", "D");
  paths.travel("C", "D");
  paths.travel("B", "C");
  paths.travel("A", "D");

  auto allPaths = paths.getAllPaths("A", "D");
  TestBase::assertEqual((int)allPaths.size(), 4, "Should have 4 paths from A to D");
}

TEST(AirPath_CycleHandling) {
  Paths paths;
  paths.travel("A", "B");
  paths.travel("B", "C");
  paths.travel("C", "A");
  paths.travel("C", "D");

  auto allPaths = paths.getAllPaths("A", "D");
  TestBase::assertEqual((int)allPaths.size(), 1, "Should have 1 path avoiding cycle");

  std::vector<std::string> expected = {"A", "B", "C", "D"};
  TestBase::assertTrue(allPaths[0] == expected, "Path should be A -> B -> C -> D");
}

TEST(AirPath_SameSourceAndDest) {
  Paths paths;
  paths.travel("A", "B");
  paths.travel("B", "A");

  auto allPaths = paths.getAllPaths("A", "A");
  TestBase::assertEqual((int)allPaths.size(), 1, "Should have 1 path (trivial)");
  TestBase::assertEqual((int)allPaths[0].size(), 1, "Trivial path has 1 node");
}

TEST(AirPath_GetDestinations) {
  Paths paths;
  paths.travel("NYC", "LA");
  paths.travel("NYC", "Chicago");
  paths.travel("NYC", "Miami");

  auto destinations = paths.getDestinations("NYC");
  TestBase::assertEqual((int)destinations.size(), 3, "NYC should have 3 destinations");

  auto emptyDest = paths.getDestinations("Unknown");
  TestBase::assertEqual((int)emptyDest.size(), 0, "Unknown city should have 0 destinations");
}

}
