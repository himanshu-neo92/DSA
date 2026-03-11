// Problem: All Paths From Start to Destination
// Given a directed graph, find all paths from a source node to a destination.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(V! / (V-P)!) worst case
// Space Complexity: O(V) - recursion stack + visited set
//
// Key concepts:
// - DFS with backtracking
// - Adjacency list representation
// - Visited set to prevent cycles
// - Backtrack by un-visiting after exploring
// =======================================================

#include "TestBase.h"
#include <unordered_map>
#include <unordered_set>

namespace AllPathsFromStartToDest {

// ========== Solution ==========
std::vector<std::vector<int>> allPaths(
    const std::unordered_map<int, std::vector<int>>& graph,
    int src, int dest) {
    // TODO: implement DFS with backtracking to find all paths
    return {};
}

// ========== Tests ==========

TEST(AllPaths_Simple) {
    std::unordered_map<int, std::vector<int>> g = {
        {0, {1, 2}}, {1, {3}}, {2, {3}}
    };
    auto paths = allPaths(g, 0, 3);
    TestBase::assertEqual(2, (int)paths.size());
}

TEST(AllPaths_SinglePath) {
    std::unordered_map<int, std::vector<int>> g = {
        {0, {1}}, {1, {2}}, {2, {3}}
    };
    auto paths = allPaths(g, 0, 3);
    TestBase::assertEqual(1, (int)paths.size());
    TestBase::assertVectorEqual({0, 1, 2, 3}, paths[0]);
}

TEST(AllPaths_NoPath) {
    std::unordered_map<int, std::vector<int>> g = {
        {0, {1}}, {2, {3}}
    };
    auto paths = allPaths(g, 0, 3);
    TestBase::assertEqual(0, (int)paths.size());
}

TEST(AllPaths_SrcEqDest) {
    std::unordered_map<int, std::vector<int>> g = {{0, {1}}, {1, {0}}};
    auto paths = allPaths(g, 0, 0);
    TestBase::assertEqual(1, (int)paths.size());
    TestBase::assertVectorEqual({0}, paths[0]);
}

TEST(AllPaths_Diamond) {
    std::unordered_map<int, std::vector<int>> g = {
        {0, {1, 2}}, {1, {2, 3}}, {2, {3}}
    };
    auto paths = allPaths(g, 0, 3);
    TestBase::assertEqual(3, (int)paths.size());
}

TEST(AllPaths_CycleAvoidance) {
    std::unordered_map<int, std::vector<int>> g = {
        {0, {1}}, {1, {2}}, {2, {0, 3}}
    };
    auto paths = allPaths(g, 0, 3);
    TestBase::assertEqual(1, (int)paths.size());
    TestBase::assertVectorEqual({0, 1, 2, 3}, paths[0]);
}

} // namespace AllPathsFromStartToDest
