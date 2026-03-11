// Problem: All Paths From Start to Destination
// Given a directed graph, find all paths from a source node to a destination node.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(V! / (V-P)!) worst case - all possible paths
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
void dfs(int curr, int dest,
         const std::unordered_map<int, std::vector<int>>& graph,
         std::unordered_set<int>& visited,
         std::vector<int>& path,
         std::vector<std::vector<int>>& result) {

    if (curr == dest) {
        result.push_back(path);
        return;
    }

    auto it = graph.find(curr);
    if (it == graph.end()) return;

    for (int neighbor : it->second) {
        if (!visited.count(neighbor)) {
            visited.insert(neighbor);
            path.push_back(neighbor);
            dfs(neighbor, dest, graph, visited, path, result);
            path.pop_back();
            visited.erase(neighbor);
        }
    }
}

std::vector<std::vector<int>> allPaths(
    const std::unordered_map<int, std::vector<int>>& graph,
    int src, int dest) {

    std::vector<std::vector<int>> result;
    std::vector<int> path = {src};
    std::unordered_set<int> visited = {src};
    dfs(src, dest, graph, visited, path, result);
    return result;
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
    // 0 -> 1 -> 3
    // 0 -> 2 -> 3
    // 0 -> 1 -> 2 -> 3
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
