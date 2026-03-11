// Problem: Serialize and Deserialize a Binary Tree
// Use level order traversal to convert a binary tree to a vector of chars
// and reconstruct the tree from that vector.
// '#' is used as the sentinel for null nodes.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - visit every node once during serialize/deserialize
// Space Complexity: O(n) - queue and output vector both hold up to n elements
//
// Key concepts:
// - BFS (level order) serialization with null sentinel
// - Trim trailing null markers to save space
// =======================================================

#include "TestBase.h"
#include <queue>

namespace SerializeBTree {

struct BTreeNode {
  char val;
  BTreeNode* left;
  BTreeNode* right;
  BTreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

const char NULL_MARKER = '#';

std::vector<char> serialize(BTreeNode* root) {
  std::vector<char> result;
  if (root == nullptr) {
    return result;
  }

  std::queue<BTreeNode*> q;
  q.push(root);

  while (!q.empty()) {
    BTreeNode* curr = q.front();
    q.pop();

    if (curr == nullptr) {
      result.push_back(NULL_MARKER);
    } else {
      result.push_back(curr->val);
      q.push(curr->left);
      q.push(curr->right);
    }
  }

  // trim trailing '#' markers since they are redundant
  while (!result.empty() && result.back() == NULL_MARKER) {
    result.pop_back();
  }

  return result;
}

BTreeNode* deserialize(const std::vector<char>& data) {
  if (data.empty()) {
    return nullptr;
  }

  BTreeNode* root = new BTreeNode(data[0]);
  std::queue<BTreeNode*> q;
  q.push(root);

  size_t i = 1;
  while (!q.empty() && i < data.size()) {
    BTreeNode* curr = q.front();
    q.pop();

    // left child
    if (i < data.size()) {
      if (data[i] != NULL_MARKER) {
        curr->left = new BTreeNode(data[i]);
        q.push(curr->left);
      }
      i++;
    }

    // right child
    if (i < data.size()) {
      if (data[i] != NULL_MARKER) {
        curr->right = new BTreeNode(data[i]);
        q.push(curr->right);
      }
      i++;
    }
  }

  return root;
}

// ========== Helpers ==========

// Compare two trees structurally and by value
bool treesEqual(BTreeNode* a, BTreeNode* b) {
  if (a == nullptr && b == nullptr) return true;
  if (a == nullptr || b == nullptr) return false;
  return a->val == b->val
      && treesEqual(a->left, b->left)
      && treesEqual(a->right, b->right);
}

// ========== Tests ==========

//       A
//      / \
//     B   C
//    / \   \
//   D   E   F
TEST(SerializeBTree_BasicTree) {
  BTreeNode* root = new BTreeNode('A');
  root->left = new BTreeNode('B');
  root->right = new BTreeNode('C');
  root->left->left = new BTreeNode('D');
  root->left->right = new BTreeNode('E');
  root->right->right = new BTreeNode('F');

  auto data = serialize(root);
    // Level order: A, B, C, D, E, #, F
    std::vector<char> expected = {'A', 'B', 'C', 'D', 'E', '#', 'F'};
    TestBase::assertVectorEqual(expected, data);

    BTreeNode* rebuilt = deserialize(data);
    TestBase::assertTrue(treesEqual(root, rebuilt));
}

TEST(SerializeBTree_EmptyTree) {
  auto data = serialize(nullptr);
  TestBase::assertEqual(0, (int)data.size());

  BTreeNode* rebuilt = deserialize(data);
  TestBase::assertTrue(rebuilt == nullptr);
}

TEST(SerializeBTree_SingleNode) {
  BTreeNode* root = new BTreeNode('X');

  auto data = serialize(root);
  std::vector<char> expected = {'X'};
  TestBase::assertVectorEqual(expected, data);

  BTreeNode* rebuilt = deserialize(data);
  TestBase::assertTrue(treesEqual(root, rebuilt));
}

//   A
//    \
//     B
//      \
//       C
TEST(SerializeBTree_SkewedRight) {
  BTreeNode* root = new BTreeNode('A');
  root->right = new BTreeNode('B');
  root->right->right = new BTreeNode('C');

  auto data = serialize(root);
  // A, #, B, #, C
  std::vector<char> expected = {'A', '#', 'B', '#', 'C'};
  TestBase::assertVectorEqual(expected, data);

  BTreeNode* rebuilt = deserialize(data);
  TestBase::assertTrue(treesEqual(root, rebuilt));
}

//       A
//      /
//     B
//    /
//   C
TEST(SerializeBTree_SkewedLeft) {
  BTreeNode* root = new BTreeNode('A');
  root->left = new BTreeNode('B');
  root->left->left = new BTreeNode('C');

  auto data = serialize(root);
  // A, B, #, C
  std::vector<char> expected = {'A', 'B', '#', 'C'};
  TestBase::assertVectorEqual(expected, data);

  BTreeNode* rebuilt = deserialize(data);
  TestBase::assertTrue(treesEqual(root, rebuilt));
}

//       1
//      / \
//     2   3
//    /   / \
//   4   5   6
//        \
//         7
TEST(SerializeBTree_Asymmetric) {
  BTreeNode* root = new BTreeNode('1');
  root->left = new BTreeNode('2');
  root->right = new BTreeNode('3');
  root->left->left = new BTreeNode('4');
  root->right->left = new BTreeNode('5');
  root->right->right = new BTreeNode('6');
  root->right->left->right = new BTreeNode('7');

  auto data = serialize(root);
  // 1, 2, 3, 4, #, 5, 6, #, #, #, 7
  std::vector<char> expected = {'1', '2', '3', '4', '#', '5', '6', '#', '#', '#', '7'};
  TestBase::assertVectorEqual(expected, data);

  BTreeNode* rebuilt = deserialize(data);
  TestBase::assertTrue(treesEqual(root, rebuilt));
}

TEST(SerializeBTree_RoundTrip_FullTree) {
  //       A
  //      / \
  //     B   C
  //    / \ / \
  //   D  E F  G
  BTreeNode* root = new BTreeNode('A');
  root->left = new BTreeNode('B');
  root->right = new BTreeNode('C');
  root->left->left = new BTreeNode('D');
  root->left->right = new BTreeNode('E');
  root->right->left = new BTreeNode('F');
  root->right->right = new BTreeNode('G');

  auto data = serialize(root);
  BTreeNode* rebuilt = deserialize(data);
  auto data2 = serialize(rebuilt);

  TestBase::assertVectorEqual(data, data2);
  TestBase::assertTrue(treesEqual(root, rebuilt));
}

} // namespace SerializeBTree
