// Problem: Number of Islands
// Given an n×m matrix, find the number of islands.
// Land is defined by 1 and water by 0.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n*m) - visit every cell at most once
// Space Complexity: O(n*m) - recursion stack in worst case (all land)
//
// Key concepts:
// - DFS flood-fill: mark visited land as 2
// - Traverse entire grid, start DFS on each unvisited land cell
// =======================================================


#include "TestBase.h"

namespace NumIslands {

  struct Pos {
    Pos(int i, int j): i(i), j(j) {}
    int i;
    int j;
  };

  bool isValid(Pos pos, int n, int m){
    if (pos.i < 0 || pos.j < 0 || pos.i >= n || pos.j >= m)
      return false;

    return true;
  }

  void searchIslands(int** mat, Pos pos, int n, int m){
    DEBUG_OUT("  searchIslands at (" << pos.i << "," << pos.j << ")");

    if (mat[pos.i][pos.j] != 1) {
      DEBUG_OUT("    skipping - not land (value=" << mat[pos.i][pos.j] << ")");
      return;
    }

    mat[pos.i][pos.j] = 2;
    DEBUG_OUT("    marked as visited");

    const std::vector<Pos> directions = { Pos(0,1), Pos(1,0), Pos(-1,0), Pos(0,-1) };

    for (const auto& dir : directions) {
      const Pos newPos(pos.i + dir.i, pos.j + dir.j);
      if (isValid(newPos, n, m) && mat[newPos.i][newPos.j] == 1) {
        searchIslands(mat, newPos, n, m);
      }
    }
  }

  int islandSearch(int** mat, int n, int m) {
    DEBUG_OUT("islandSearch called with n=" << n << ", m=" << m);
    int numIslands = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mat[i][j] == 1) {
          DEBUG_OUT("Found new island starting at (" << i << "," << j << ")");
          numIslands++;
          searchIslands(mat, Pos(i, j), n, m);
        }
      }
    }

    DEBUG_OUT("Total islands found: " << numIslands);
    return numIslands;
  }

  // Helper function to create a 2D matrix from a vector of vectors
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

  // Helper function to free a 2D matrix
  void freeMatrix(int** mat, int n) {
    if (mat == nullptr) return;
    for (int i = 0; i < n; ++i) {
      delete[] mat[i];
    }
    delete[] mat;
  }

  // Helper to print matrix for debugging
  void printMatrix(int** mat, int n, int m) {
    DEBUG_OUT("Matrix state:");
    for (int i = 0; i < n; ++i) {
      std::string row = "  ";
      for (int j = 0; j < m; ++j) {
        row += std::to_string(mat[i][j]) + " ";
      }
      DEBUG_OUT(row);
    }
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
  DEBUG_OUT("Input: 3x3 grid of all 1s");
  NumIslands::printMatrix(mat, 3, 3);

  int result = NumIslands::islandSearch(mat, 3, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

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
  DEBUG_OUT("Input: 4 separate islands in corners");
  NumIslands::printMatrix(mat, 3, 3);

  int result = NumIslands::islandSearch(mat, 3, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 4");

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
  DEBUG_OUT("Input: All water");
  NumIslands::printMatrix(mat, 3, 3);

  int result = NumIslands::islandSearch(mat, 3, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 0");

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
  DEBUG_OUT("Input: L-shaped island");
  NumIslands::printMatrix(mat, 3, 3);

  int result = NumIslands::islandSearch(mat, 3, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

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
  DEBUG_OUT("Input: 3 islands in a 4x5 grid");
  NumIslands::printMatrix(mat, 4, 5);

  int result = NumIslands::islandSearch(mat, 4, 5);
  DEBUG_OUT("Result: " << result << ", Expected: 3");

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
  DEBUG_OUT("Input: Single cell island in center");
  NumIslands::printMatrix(mat, 3, 3);

  int result = NumIslands::islandSearch(mat, 3, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

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
  DEBUG_OUT("Input: Horizontal line island");
  NumIslands::printMatrix(mat, 3, 5);

  int result = NumIslands::islandSearch(mat, 3, 5);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_VerticalLine) {
  std::vector<std::vector<int>> grid = {
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: Vertical line island");
  NumIslands::printMatrix(mat, 4, 3);

  int result = NumIslands::islandSearch(mat, 4, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_DiagonalNotConnected) {
  // Diagonals are NOT connected (only 4-directional movement)
  std::vector<std::vector<int>> grid = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: Diagonal cells (not connected)");
  NumIslands::printMatrix(mat, 3, 3);

  int result = NumIslands::islandSearch(mat, 3, 3);
  DEBUG_OUT("Result: " << result << ", Expected: 3");

  NumIslands::freeMatrix(mat, 3);
  TestBase::assertEqual(3, result);
}

TEST(NumIslands_LargeGrid) {
  std::vector<std::vector<int>> grid = {
    {1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: 4x5 grid with 3 islands");
  NumIslands::printMatrix(mat, 4, 5);

  int result = NumIslands::islandSearch(mat, 4, 5);
  DEBUG_OUT("Result: " << result << ", Expected: 3");

  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(3, result);
}

TEST(NumIslands_SingleRow) {
  std::vector<std::vector<int>> grid = {
    {1, 0, 1, 0, 1, 1, 0, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: Single row");
  NumIslands::printMatrix(mat, 1, 8);

  int result = NumIslands::islandSearch(mat, 1, 8);
  DEBUG_OUT("Result: " << result << ", Expected: 4");

  NumIslands::freeMatrix(mat, 1);
  TestBase::assertEqual(4, result);
}

TEST(NumIslands_SingleColumn) {
  std::vector<std::vector<int>> grid = {
    {1},
    {0},
    {1},
    {1},
    {0},
    {1}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: Single column");
  NumIslands::printMatrix(mat, 6, 1);

  int result = NumIslands::islandSearch(mat, 6, 1);
  DEBUG_OUT("Result: " << result << ", Expected: 3");

  NumIslands::freeMatrix(mat, 6);
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
  DEBUG_OUT("Input: Ring-shaped island");
  NumIslands::printMatrix(mat, 4, 4);

  int result = NumIslands::islandSearch(mat, 4, 4);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

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
  DEBUG_OUT("Input: Checkerboard pattern");
  NumIslands::printMatrix(mat, 4, 4);

  int result = NumIslands::islandSearch(mat, 4, 4);
  DEBUG_OUT("Result: " << result << ", Expected: 8");

  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(8, result);
}

TEST(NumIslands_LeetCodeExample1) {
  // LeetCode example 1
  std::vector<std::vector<int>> grid = {
    {1, 1, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: LeetCode example 1");
  NumIslands::printMatrix(mat, 4, 5);

  int result = NumIslands::islandSearch(mat, 4, 5);
  DEBUG_OUT("Result: " << result << ", Expected: 1");

  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(1, result);
}

TEST(NumIslands_LeetCodeExample2) {
  // LeetCode example 2
  std::vector<std::vector<int>> grid = {
    {1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1}
  };
  int** mat = NumIslands::createMatrix(grid);
  DEBUG_OUT("Input: LeetCode example 2");
  NumIslands::printMatrix(mat, 4, 5);

  int result = NumIslands::islandSearch(mat, 4, 5);
  DEBUG_OUT("Result: " << result << ", Expected: 3");

  NumIslands::freeMatrix(mat, 4);
  TestBase::assertEqual(3, result);
}
