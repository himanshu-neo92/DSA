// Problem: Binary Tree Level Order Traversal
// Given a binary tree, return the level order traversal of its nodes' values
// (i.e., from left to right, level by level).
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Visit every node once
// Space Complexity: O(w) - Queue holds at most one level (max width w)
//
// Key concepts:
// - BFS using a queue
// - Process one level at a time by capturing queue size before draining
// - Each level produces one vector in the result
// =======================================================

#include "TestBase.h"
#include <queue>

namespace LevelOrder {

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ========== Solution ==========
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    // TODO: implement level order traversal using BFS
    return {};
}

// ========== Tests ==========

//       1
//      / \
//     2   3
//    / \   \
//   4   5   6
TEST(LevelOrder_BasicTree) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->right = new TreeNode(6);

  auto result = levelOrder(root);

  TestBase::assertEqual(3, (int)result.size());
  TestBase::assertVectorEqual({1}, result[0]);
  TestBase::assertVectorEqual({2, 3}, result[1]);
  TestBase::assertVectorEqual({4, 5, 6}, result[2]);
}

TEST(LevelOrder_SingleNode) {
  TreeNode* root = new TreeNode(42);

  auto result = levelOrder(root);

  TestBase::assertEqual(1, (int)result.size());
  TestBase::assertVectorEqual({42}, result[0]);
}

TEST(LevelOrder_EmptyTree) {
  auto result = levelOrder(nullptr);

  TestBase::assertEqual(0, (int)result.size());
}

TEST(LevelOrder_SkewedRight) {
  TreeNode* root = new TreeNode(1);
  root->right = new TreeNode(2);
  root->right->right = new TreeNode(3);

  auto result = levelOrder(root);

  TestBase::assertEqual(3, (int)result.size());
  TestBase::assertVectorEqual({1}, result[0]);
  TestBase::assertVectorEqual({2}, result[1]);
  TestBase::assertVectorEqual({3}, result[2]);
}

TEST(LevelOrder_SkewedLeft) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->left->left = new TreeNode(3);

  auto result = levelOrder(root);

  TestBase::assertEqual(3, (int)result.size());
  TestBase::assertVectorEqual({1}, result[0]);
  TestBase::assertVectorEqual({2}, result[1]);
  TestBase::assertVectorEqual({3}, result[2]);
}

} // namespace LevelOrder
