// Problem: Depth of a Binary Tree
// Given a binary tree, find its maximum depth (number of levels).
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Visit every node once
// Space Complexity: O(n) - Queue stores up to n/2 nodes at widest level
//
// Alternative approaches:
// - Recursive DFS: O(n) time, O(h) space where h = height
// - BFS (level order): O(n) time, O(w) space where w = max width
//
// Hint: Use level order traversal (BFS) and count levels,
// or use recursive DFS returning max(left, right) + 1
// =======================================================

#include "TestBase.h"

namespace DepthOfATree {

struct Node {
    int data;
    Node* left;
    Node* right;
};

// ========== Solution ==========
int depthOfATree(Node* head) {
    // TODO: implement your solution here
    return 0;
}

// ========== Helpers ==========
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
