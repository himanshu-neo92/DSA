/*
Problem: Number of Islands
Given an n×m matrix, find the number of islands.
Land is defined by 1 and water by 0.

==================== PERFORMANCE ====================
Time Complexity:  O(n * m) - Visit each cell at most twice
Space Complexity: O(n * m) - Recursion stack in worst case

Key concepts:
- Traverse the entire matrix
- When a 1 is found, increment island count and DFS to mark all connected land
- DFS marks visited cells as 2 to avoid revisiting
- Only 4-directional connectivity (up, down, left, right)
=======================================================
*/

#include "TestBase.h"

namespace NumIslands {

struct Pos {
    Pos(int i, int j): i(i), j(j) {}
    int i;
    int j;
};

// ========== Solution ==========
bool isValid(Pos pos, int n, int m) {
    if (pos.i < 0 || pos.j < 0 || pos.i >= n || pos.j >= m)
        return false;
    return true;
}

void searchIslands(int** mat, Pos pos, int n, int m) {
    // TODO: implement DFS to mark all connected land cells
}

int islandSearch(int** mat, int n, int m) {
    // TODO: implement - traverse matrix, count islands
    return 0;
}

// ========== Helpers ==========
int** createMatrix(const std::vector<std::vector<int>>& grid) {
    if (grid.empty()) return nullptr;
    int n = grid.size();
    int** mat = new int*[n];
    for (int i = 0; i < n; ++i) {
        mat[i] = new int[grid[i].size()];
        for (size_t j = 0; j < grid[i].size(); ++j) {
            mat[i][j] = grid[i][j];
        }
    }
    return mat;
}

void freeMatrix(int** mat, int n) {
    if (mat == nullptr) return;
    for (int i = 0; i < n; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

}

// ==================== TEST CASES ====================

TEST(NumIslands_SingleIsland) {
  std::vector<std::vector<int>> grid = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 3);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_MultipleIslands) {
  std::vector<std::vector<int>> grid = {
    {1, 0, 1},
    {0, 0, 0},
    {1, 0, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 3);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(4, result);
}

TEST(NumIslands_NoIslands) {
  std::vector<std::vector<int>> grid = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 3);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(0, result);
}

TEST(NumIslands_LShapedIsland) {
  std::vector<std::vector<int>> grid = {
    {1, 0, 0},
    {1, 0, 0},
    {1, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 3);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_TwoSeparateIslands) {
  std::vector<std::vector<int>> grid = {
    {1, 1, 0, 0, 1},
    {1, 1, 0, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 4, 5);
  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(3, result);
}

TEST(NumIslands_SingleCellIsland) {
  std::vector<std::vector<int>> grid = {
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 3);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_HorizontalLine) {
  std::vector<std::vector<int>> grid = {
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 5);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_DiagonalNotConnected) {
  std::vector<std::vector<int>> grid = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 3, 3);
  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(3, result);
}

TEST(NumIslands_RingShape) {
  std::vector<std::vector<int>> grid = {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 4, 4);
  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_Checkerboard) {
  std::vector<std::vector<int>> grid = {
    {1, 0, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 4, 4);
  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(8, result);
}

TEST(NumIslands_LeetCodeExample1) {
  std::vector<std::vector<int>> grid = {
    {1, 1, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 4, 5);
  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_LeetCodeExample2) {
  std::vector<std::vector<int>> grid = {
    {1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  int result = NumIslands::islandSearch(mat, 4, 5);
  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(3, result);
}
