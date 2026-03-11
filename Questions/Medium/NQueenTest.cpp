// Problem: N-Queens (LeetCode 51)
// Place n queens on an n×n chessboard so no two queens attack each other.
// Return the number of distinct solutions.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n!) - Backtracking with pruning
// Space Complexity: O(n) - Column and diagonal tracking
//
// Key concepts:
// - Backtracking: try placing a queen in each column of each row
// - Track occupied columns, diagonals (row-col), anti-diagonals (row+col)
// - If placement is valid, recurse to next row
// =======================================================

#include "TestBase.h"
#include <unordered_set>

namespace NQueen {

// ========== Solution ==========
int totalNQueens(int n) {
    // TODO: implement your solution here
    return 0;
}

// ========== Tests ==========

TEST(NQueen_1) { TestBase::assertEqual(1, totalNQueens(1)); }
TEST(NQueen_4) { TestBase::assertEqual(2, totalNQueens(4)); }
TEST(NQueen_5) { TestBase::assertEqual(10, totalNQueens(5)); }
TEST(NQueen_6) { TestBase::assertEqual(4, totalNQueens(6)); }
TEST(NQueen_8) { TestBase::assertEqual(92, totalNQueens(8)); }

} // namespace NQueen
