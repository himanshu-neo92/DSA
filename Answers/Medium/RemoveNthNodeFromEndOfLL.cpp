// Problem: Remove Nth Node From End of Linked List
// Given a linked list, remove the nth node from the end and return the head.
// Use two pointers: advance fast by n, then move both until fast reaches end.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - single pass through the list
// Space Complexity: O(1) - only two pointer variables
//
// Key concepts:
// - Two-pointer technique with fixed gap
// - Edge cases: removing head node, k exceeds list length
// =======================================================

#include "TestBase.h"

namespace RemoveNthNode {

  struct LLNode {

    int val;
    LLNode* Next;

    LLNode(): val(0), Next(nullptr) {}
    LLNode(int v): val(v), Next(nullptr) {}
  };

  LLNode* removeNthNode(LLNode* head, int k) {

    if ( k <= 0 ) {
      return head;
    }

    LLNode* fastNode = head;
    while (k > 0 && fastNode) {
      fastNode = fastNode->Next;
      --k;
    }

    if (k > 0) {
      return head;
    }

    LLNode* slowNode = head;

    // if we need to remove the head node
    if (fastNode == nullptr) {

      head = head->Next;
      delete slowNode;
      return head;
    }

    while (fastNode->Next) {
            fastNode = fastNode->Next;
            slowNode = slowNode->Next;
    }

    LLNode* toDel = slowNode->Next;
    slowNode->Next = toDel->Next;
    delete toDel;

    return head;

  }

  // ==================== HELPER FUNCTIONS ====================

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
  // Note: removeNthNode now returns LLNode* (the new head) instead of bool

  TEST(RemoveNthNode_RemoveLastNode) {
    // List: 1 -> 2 -> 3 -> 4 -> 5, remove 1st from end (value 5)
    LLNode* head = createLinkedList({1, 2, 3, 4, 5});
    head = removeNthNode(head, 1);

    TestBase::assertTrue(head != nullptr, "Head should not be null after removing last node");
    std::vector<int> expected = {1, 2, 3, 4};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing last node");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_RemoveMiddleNode) {
    // List: 1 -> 2 -> 3 -> 4 -> 5, remove 3rd from end (value 3)
    LLNode* head = createLinkedList({1, 2, 3, 4, 5});
    head = removeNthNode(head, 3);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1, 2, 4, 5};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing middle node");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_RemoveSecondToLastNode) {
    // List: 1 -> 2 -> 3 -> 4 -> 5, remove 2nd from end (value 4)
    LLNode* head = createLinkedList({1, 2, 3, 4, 5});
    head = removeNthNode(head, 2);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1, 2, 3, 5};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing 2nd to last node");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_KExceedsListLength) {
    // List: 1 -> 2 -> 3, try to remove 5th from end (doesn't exist)
    LLNode* head = createLinkedList({1, 2, 3});
    LLNode* result = removeNthNode(head, 5);

    // When k exceeds list length, the original head should be returned unchanged
    TestBase::assertTrue(result == head, "Should return original head when k exceeds list length");
    std::vector<int> expected = {1, 2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(result), "List should remain unchanged");

    freeLinkedList(result);
  }

  TEST(RemoveNthNode_KEqualsListLength) {
    // List: 1 -> 2 -> 3, remove 3rd from end (value 1, the head)
    LLNode* head = createLinkedList({1, 2, 3});
    head = removeNthNode(head, 3);

    TestBase::assertTrue(head != nullptr, "Head should not be null after removing old head");
    std::vector<int> expected = {2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing head");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_TwoElementListRemoveLast) {
    // List: 1 -> 2, remove 1st from end (value 2)
    LLNode* head = createLinkedList({1, 2});
    head = removeNthNode(head, 1);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing last of 2 elements");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_TwoElementListRemoveFirst) {
    // List: 1 -> 2, remove 2nd from end (value 1, the head)
    LLNode* head = createLinkedList({1, 2});
    head = removeNthNode(head, 2);

    TestBase::assertTrue(head != nullptr, "Head should not be null after removing old head");
    std::vector<int> expected = {2};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing head from 2-element list");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_LongerList) {
    // List: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
    // Remove 4th from end (value 7)
    LLNode* head = createLinkedList({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    head = removeNthNode(head, 4);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 8, 9, 10};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing 4th from end");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_KIsZero) {
    // List: 1 -> 2 -> 3, k = 0 (invalid - should return list unchanged)
    LLNode* head = createLinkedList({1, 2, 3});
    LLNode* result = removeNthNode(head, 0);

    // k=0 is handled at the start, returning head unchanged
    TestBase::assertTrue(result == head, "Should return original head when k is 0");
    std::vector<int> expected = {1, 2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(result), "List should remain unchanged for k=0");

    freeLinkedList(result);
  }

  TEST(RemoveNthNode_ListWithDuplicateValues) {
    // List: 1 -> 1 -> 1 -> 1 -> 1, remove 3rd from end
    LLNode* head = createLinkedList({1, 1, 1, 1, 1});
    head = removeNthNode(head, 3);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {1, 1, 1, 1};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing from duplicates");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_RemoveSecondFromFiveElements) {
    // List: 10 -> 20 -> 30 -> 40 -> 50, remove 2nd from end (value 40)
    LLNode* head = createLinkedList({10, 20, 30, 40, 50});
    head = removeNthNode(head, 2);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {10, 20, 30, 50};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing 40");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_RemoveFourthFromSixElements) {
    // List: 10 -> 20 -> 30 -> 40 -> 50 -> 60, remove 4th from end (value 30)
    LLNode* head = createLinkedList({10, 20, 30, 40, 50, 60});
    head = removeNthNode(head, 4);

    TestBase::assertTrue(head != nullptr, "Head should not be null");
    std::vector<int> expected = {10, 20, 40, 50, 60};
    TestBase::assertVectorEqual(expected, linkedListToVector(head), "List after removing 30");

    freeLinkedList(head);
  }

  TEST(RemoveNthNode_SingleElement) {
    // List: 42, remove 1st from end (the only element)
    LLNode* head = createLinkedList({42});
    head = removeNthNode(head, 1);

    // After removing the only element, head should be nullptr
    TestBase::assertTrue(head == nullptr, "Head should be null after removing only element");
  }

  TEST(RemoveNthNode_NegativeK) {
    // List: 1 -> 2 -> 3, k = -1 (invalid)
    LLNode* head = createLinkedList({1, 2, 3});
    LLNode* result = removeNthNode(head, -1);

    // Negative k should not remove anything (k > 0 check fails in loop)
    TestBase::assertTrue(result == head, "Should return original head for negative k");
    std::vector<int> expected = {1, 2, 3};
    TestBase::assertVectorEqual(expected, linkedListToVector(result), "List should remain unchanged for negative k");

    freeLinkedList(result);
  }

}
