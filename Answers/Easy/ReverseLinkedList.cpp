
// Problem: Reverse Linked List
// Reverse a singly linked list in-place
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Single pass through the list
// Space Complexity: O(1) - Only uses 3 pointers (prev, curr, next)
//
// Alternative approaches:
// - Recursive: O(n) time, O(n) space - Stack frames for each node
// - Create new list: O(n) time, O(n) space - Wastes memory
// - Stack-based: O(n) time, O(n) space - Store all nodes, then rebuild
//
// Why this approach is optimal:
// - In-place reversal uses constant extra memory
// - Single pass is optimal for linked list traversal
// - No function call overhead (unlike recursion)
//
// Cache considerations:
// - Linked lists have poor cache locality (nodes scattered in memory)
// - Consider using std::vector if random access is needed
// - For cache-friendly lists, use memory pools or arena allocators
//
// Memory leak warning:
// - Current test does not free allocated nodes
// - In production, use smart pointers (std::unique_ptr)
// - Or implement proper cleanup in destructor
// =======================================================

#include "TestBase.h"

namespace ReverseLinkedList {

  struct Node {
    int data;
    Node* next;
  };

Node* reverseLinkedList(Node* head) {
  Node* prev = nullptr;
  Node* curr = head;
  Node* next = nullptr;

  while (curr != nullptr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  head = prev;
  return head;
}

TEST(ReverseLinkedList_Basic) {
  Node* head = new Node();
  head->data = 1;
  head->next = new Node();
  head->next->data = 2;
  head->next->next = new Node();
  head->next->next->data = 3;
  head->next->next->next = nullptr;

  head = reverseLinkedList(head);

  TestBase::assertEqual(3, head->data);
  TestBase::assertEqual(2, head->next->data);
  TestBase::assertEqual(1, head->next->next->data);

  delete head->next->next;
  delete head->next;
  delete head;
}

TEST(ReverseLinkedList_NullHead) {
  Node* head = nullptr;
  head = reverseLinkedList(head);
  TestBase::assertTrue(head == nullptr, "Reversing null should return null");
}

TEST(ReverseLinkedList_SingleNode) {
  Node* head = new Node();
  head->data = 42;
  head->next = nullptr;

  head = reverseLinkedList(head);

  TestBase::assertEqual(42, head->data, "Single node value preserved");
  TestBase::assertTrue(head->next == nullptr, "Single node next is null");

  delete head;
}

TEST(ReverseLinkedList_TwoNodes) {
  Node* head = new Node();
  head->data = 1;
  head->next = new Node();
  head->next->data = 2;
  head->next->next = nullptr;

  head = reverseLinkedList(head);

  TestBase::assertEqual(2, head->data, "First node after reverse");
  TestBase::assertEqual(1, head->next->data, "Second node after reverse");
  TestBase::assertTrue(head->next->next == nullptr, "Tail is null");

  delete head->next;
  delete head;
}

TEST(ReverseLinkedList_FiveNodes) {
  Node* n5 = new Node{5, nullptr};
  Node* n4 = new Node{4, n5};
  Node* n3 = new Node{3, n4};
  Node* n2 = new Node{2, n3};
  Node* head = new Node{1, n2};

  head = reverseLinkedList(head);

  TestBase::assertEqual(5, head->data);
  TestBase::assertEqual(4, head->next->data);
  TestBase::assertEqual(3, head->next->next->data);
  TestBase::assertEqual(2, head->next->next->next->data);
  TestBase::assertEqual(1, head->next->next->next->next->data);
  TestBase::assertTrue(head->next->next->next->next->next == nullptr, "Tail is null");

  Node* curr = head;
  while (curr) { Node* tmp = curr; curr = curr->next; delete tmp; }
}

} // namespace ReverseLinkedList
