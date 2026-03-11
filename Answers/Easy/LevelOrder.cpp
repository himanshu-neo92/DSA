// Problem: Binary Tree Level Order Traversal
// Given a binary tree, return the level order traversal of its nodes' values
// (i.e., from left to right, level by level).
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - visit every node exactly once
// Space Complexity: O(w) - queue holds at most one level, w = max width
//
// Key concepts:
// - BFS using a queue
// - Process nodes level by level using size snapshot
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

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
  std::vector<std::vector<int>> result;
  if (root == nullptr) {
    return result;
  }

  std::queue<TreeNode*> q;
  q.push(root);

  while (!q.empty()) {

    // get the size
    int levelSize = q.size();

    // keeping track of the curr level
    std::vector<int> currentLevel;

    // drain till the size we captured before.
    for (int i = 0; i < levelSize; ++i) {
      TreeNode* node = q.front();
      q.pop();
      currentLevel.push_back(node->val);

      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }

    result.push_back(currentLevel);
  }

  return result;
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

//   1
//    \
//     2
//      \
//       3
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

//         1
//        /
//       2
//      /
//     3
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
