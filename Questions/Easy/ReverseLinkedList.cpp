// Problem: Reverse Linked List
// Reverse a singly linked list in-place.
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
// Key concepts:
// - Three pointers: prev, curr, next
// - At each step: save next, reverse link, advance pointers
// =======================================================

#include "TestBase.h"

namespace ReverseLinkedList {

struct Node {
    int data;
    Node* next;
};

// ========== Solution ==========
Node* reverseLinkedList(Node* head) {
    // TODO: implement your solution here
    return head;
}

// ========== Tests ==========
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

} // namespace ReverseLinkedList
