/*
Problem: Remove Nth Node From End of Linked List
Given a linked list, remove the nth node from the end and return the head.

==================== PERFORMANCE ====================
Time Complexity:  O(n) - Single pass with two pointers
Space Complexity: O(1) - Only uses two pointers

Key concepts:
- Two-pointer technique: fast and slow
- Move fast pointer n positions ahead
- Then move both until fast reaches the end
- Slow pointer will be at the node before the one to remove

Edge cases:
1. Not enough nodes: don't do anything
2. Removing the head: need special handling
3. k <= 0: invalid, return unchanged
=======================================================
*/

#include "TestBase.h"

namespace RemoveNthNode {

struct LLNode {
    int val;
    LLNode* Next;

    LLNode(): val(0), Next(nullptr) {}
    LLNode(int v): val(v), Next(nullptr) {}
};

// ========== Solution ==========
LLNode* removeNthNode(LLNode* head, int k) {
    // TODO: implement your solution here
    return head;
}

// ========== Helpers ==========
LLNode* createLinkedList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    auto head = new LLNode(values[0]);
    LLNode* current = head;
    for (size_t i = 1; i < values.size(); i++) {
        current->Next = new LLNode(values[i]);
        current = current->Next;
    }
    return head;
}

std::vector<int> linkedListToVector(LLNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->Next;
    }
    return result;
}

void freeLinkedList(LLNode* head) {
    while (head) {
        LLNode* temp = head;
        head = head->Next;
        delete temp;
    }
}

// ==================== TEST CASES ====================

TEST(RemoveNthNode_RemoveLastNode) {
    LLNode* head = createLinkedList({1, 2, 3, 4, 5});
    head = removeNthNode(head, 1);
    TestBase::assertTrue(head != nullptr, "Head should not be null after removing last node");
    std::vector<int> expected = {1, 2, 3, 4};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing last node");
    freeLinkedList(head);
}

TEST(RemoveNthNode_RemoveMiddleNode) {
    LLNode* head = createLinkedList({1, 2, 3, 4, 5});
    head = removeNthNode(head, 3);
    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1, 2, 4, 5};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing middle node");
    freeLinkedList(head);
}

TEST(RemoveNthNode_RemoveSecondToLastNode) {
    LLNode* head = createLinkedList({1, 2, 3, 4, 5});
    head = removeNthNode(head, 2);
    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1, 2, 3, 5};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing 2nd to last node");
    freeLinkedList(head);
}

TEST(RemoveNthNode_KExceedsListLength) {
    LLNode* head = createLinkedList({1, 2, 3});
    LLNode* result = removeNthNode(head, 5);
    TestBase::assertTrue(result == head, "Should return original head when k exceeds list length");
    std::vector<int> expected = {1, 2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(result), "List should remain unchanged");
    freeLinkedList(result);
}

TEST(RemoveNthNode_KEqualsListLength) {
    LLNode* head = createLinkedList({1, 2, 3});
    head = removeNthNode(head, 3);
    TestBase::assertTrue(head != nullptr, "Head should not be null after removing old head");
    std::vector<int> expected = {2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing head");
    freeLinkedList(head);
}

TEST(RemoveNthNode_TwoElementListRemoveLast) {
    LLNode* head = createLinkedList({1, 2});
    head = removeNthNode(head, 1);
    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing last of 2 elements");
    freeLinkedList(head);
}

TEST(RemoveNthNode_TwoElementListRemoveFirst) {
    LLNode* head = createLinkedList({1, 2});
    head = removeNthNode(head, 2);
    TestBase::assertTrue(head != nullptr, "Head should not be null after removing old head");
    std::vector<int> expected = {2};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing head from 2-element list");
    freeLinkedList(head);
}

TEST(RemoveNthNode_SingleElement) {
    LLNode* head = createLinkedList({42});
    head = removeNthNode(head, 1);
    TestBase::assertTrue(head == nullptr, "Head should be null after removing only element");
}

TEST(RemoveNthNode_KIsZero) {
    LLNode* head = createLinkedList({1, 2, 3});
    LLNode* result = removeNthNode(head, 0);
    TestBase::assertTrue(result == head, "Should return original head when k is 0");
    std::vector<int> expected = {1, 2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(result), "List should remain unchanged for k=0");
    freeLinkedList(result);
}

TEST(RemoveNthNode_NegativeK) {
    LLNode* head = createLinkedList({1, 2, 3});
    LLNode* result = removeNthNode(head, -1);
    TestBase::assertTrue(result == head, "Should return original head for negative k");
    std::vector<int> expected = {1, 2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(result), "List should remain unchanged for negative k");
    freeLinkedList(result);
}

}
