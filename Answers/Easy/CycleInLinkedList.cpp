// Problem: Cycle in Linked List
// Given a linked list, determine if it has a cycle.
// A cycle exists if a node's next pointer points back to a previous node.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Floyd's Tortoise and Hare
// Space Complexity: O(1) - Only two pointers
//
// Alternative approaches:
// - Hash set of visited nodes: O(n) time, O(n) space
// - Modify node structure (mark visited): O(n) time, O(1) space but destructive
//
// Why Floyd's algorithm works:
// - Slow pointer moves 1 step, fast moves 2 steps
// - If cycle exists, fast will eventually meet slow inside the cycle
// - If no cycle, fast reaches nullptr
// =======================================================

#include "TestBase.h"

namespace CycleInLinkedList {

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// ========== Solution ==========
bool hasCycle(Node* head) {
    if (head == nullptr) return false;

    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }

    return false;
}

// ========== Helpers ==========
Node* createList(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    Node* head = new Node(vals[0]);
    Node* curr = head;
    for (size_t i = 1; i < vals.size(); ++i) {
        curr->next = new Node(vals[i]);
        curr = curr->next;
    }
    return head;
}

void freeList(Node* head, bool hasCycleBit) {
    if (hasCycleBit) {
        // Break cycle first using Floyd's
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        if (fast && fast->next) {
            slow = head;
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
            fast->next = nullptr;
        }
    }
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ========== Tests ==========

TEST(CycleInLinkedList_NoCycle) {
    Node* head = createList({1, 2, 3, 4, 5});
    TestBase::assertFalse(hasCycle(head), "Linear list should have no cycle");
    freeList(head, false);
}

TEST(CycleInLinkedList_WithCycle) {
    Node* head = createList({1, 2, 3, 4, 5});
    // Create cycle: 5 -> 3
    Node* tail = head;
    Node* cycleEntry = nullptr;
    int idx = 0;
    while (tail->next) {
        if (idx == 2) cycleEntry = tail;
        tail = tail->next;
        idx++;
    }
    tail->next = cycleEntry;

    TestBase::assertTrue(hasCycle(head), "List with cycle should be detected");
    freeList(head, true);
}

TEST(CycleInLinkedList_SingleNodeNoCycle) {
    Node* head = new Node(1);
    TestBase::assertFalse(hasCycle(head), "Single node without self-loop has no cycle");
    delete head;
}

TEST(CycleInLinkedList_SingleNodeSelfLoop) {
    Node* head = new Node(1);
    head->next = head;
    TestBase::assertTrue(hasCycle(head), "Single node with self-loop is a cycle");
    head->next = nullptr;
    delete head;
}

TEST(CycleInLinkedList_TwoNodesCycle) {
    Node* a = new Node(1);
    Node* b = new Node(2);
    a->next = b;
    b->next = a;
    TestBase::assertTrue(hasCycle(a), "Two nodes pointing to each other is a cycle");
    b->next = nullptr;
    delete a;
    delete b;
}

TEST(CycleInLinkedList_NullHead) {
    TestBase::assertFalse(hasCycle(nullptr), "Null head has no cycle");
}

TEST(CycleInLinkedList_CycleAtHead) {
    Node* head = createList({1, 2, 3});
    // Tail points back to head
    Node* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = head;
    TestBase::assertTrue(hasCycle(head), "Cycle back to head should be detected");
    tail->next = nullptr;
    freeList(head, false);
}

} // namespace CycleInLinkedList
