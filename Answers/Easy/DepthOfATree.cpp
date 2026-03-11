// Problem: Depth of a Tree
// Given a binary tree, find its maximum depth (number of levels)
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Every node is visited exactly once
// Space Complexity: O(w) - Queue holds at most one level's worth of nodes, where w is max width
//
// Alternative approaches:
// - Recursive DFS: O(n) time, O(h) space where h is tree height (call stack)
// - Iterative DFS with explicit stack: O(n) time, O(h) space
//
// Why this approach is optimal:
// - BFS level-order traversal naturally counts levels as it progresses
// - O(n) time is optimal since every node must be examined
// - Avoids stack overflow risk on deeply skewed trees unlike recursive DFS
// =======================================================

#include "TestBase.h"

namespace DepthOfATree {
  struct Node {
    int data;
    Node* left;
    Node* right;
  };

  int depthOfATree(Node* head) {

    // Create a queue and push the head node in
    std::queue<Node> visitQueue;
    int treeDepth = 0;
    visitQueue.push(*head);

    // Till there are no elements left in the queue
    while (!visitQueue.empty()) {

      // Drain the elements we started with add add the children.
      const int visitedSize = visitQueue.size();
      for ( int i = 0; i< visitedSize; ++i) {
      const Node& curr = visitQueue.front();
      visitQueue.pop();
      if (curr.left) {
      visitQueue.push(*curr.left);
      }
      if (curr.right) {
        visitQueue.push(*curr.right);
      }
    }

    // We have reached the next level.
      treeDepth++;
    }
    return treeDepth;
  }

  Node* createNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
  }

  void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

} // namespace DepthOfATree

// ==================== TEST CASES ====================

TEST(DepthOfATree_SingleNode) {
    auto* root = DepthOfATree::createNode(1);
    TestBase::assertEqual(1, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_TwoLevelsLeft) {
    auto* root = DepthOfATree::createNode(1);
    root->left = DepthOfATree::createNode(2);
    TestBase::assertEqual(2, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_TwoLevelsRight) {
    auto* root = DepthOfATree::createNode(1);
    root->right = DepthOfATree::createNode(2);
    TestBase::assertEqual(2, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_TwoLevelsFull) {
    auto* root = DepthOfATree::createNode(1);
    root->left = DepthOfATree::createNode(2);
    root->right = DepthOfATree::createNode(3);
    TestBase::assertEqual(2, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_ThreeLevels) {
    auto* root = DepthOfATree::createNode(1);
    root->left = DepthOfATree::createNode(2);
    root->right = DepthOfATree::createNode(3);
    root->left->left = DepthOfATree::createNode(4);
    root->left->right = DepthOfATree::createNode(5);
    TestBase::assertEqual(3, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_LeftSkewed) {
    auto* root = DepthOfATree::createNode(1);
    root->left = DepthOfATree::createNode(2);
    root->left->left = DepthOfATree::createNode(3);
    root->left->left->left = DepthOfATree::createNode(4);
    TestBase::assertEqual(4, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_RightSkewed) {
    auto* root = DepthOfATree::createNode(1);
    root->right = DepthOfATree::createNode(2);
    root->right->right = DepthOfATree::createNode(3);
    root->right->right->right = DepthOfATree::createNode(4);
    TestBase::assertEqual(4, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_CompleteBinaryTree) {
    auto* root = DepthOfATree::createNode(1);
    root->left = DepthOfATree::createNode(2);
    root->right = DepthOfATree::createNode(3);
    root->left->left = DepthOfATree::createNode(4);
    root->left->right = DepthOfATree::createNode(5);
    root->right->left = DepthOfATree::createNode(6);
    root->right->right = DepthOfATree::createNode(7);
    TestBase::assertEqual(3, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}

TEST(DepthOfATree_Unbalanced) {
    auto* root = DepthOfATree::createNode(1);
    root->left = DepthOfATree::createNode(2);
    root->left->right = DepthOfATree::createNode(3);
    root->left->right->left = DepthOfATree::createNode(4);
    root->left->right->left->right = DepthOfATree::createNode(5);
    TestBase::assertEqual(5, DepthOfATree::depthOfATree(root));
    DepthOfATree::deleteTree(root);
}
