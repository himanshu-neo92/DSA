// Problem: Merge K Sorted Lists
// Merge k sorted linked lists into one sorted linked list.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(N log k) - pairwise merge halves k each round
// Space Complexity: O(1) - in-place pointer manipulation
//
// Key concepts:
// - Pairwise (divide-and-conquer) merge strategy
// - Merge two sorted lists at a time
// =======================================================

#include "TestBase.h"

namespace MergeKSortedList {

struct Node {
  int data;
  Node* next;
};

Node* mergeTwoLists(Node* l1, Node* l2) {
  if( l1 == nullptr) {
    return l2;
  }

  if ( l2 == nullptr) {
    return l1;
  }
  Node* newList = nullptr;

  if ( l1->data < l2->data) {
    newList = l1;
    l1 = l1->next;
    newList->next = nullptr;
  } else {
    newList = l2;
    l2 = l2->next;
    newList->next = nullptr;
  }

  Node* curr = newList;

  while (l1 !=nullptr && l2 != nullptr) {
    if (l1->data < l2->data) {
      curr->next = l1;
      l1 = l1->next;
      curr = curr->next;
      curr->next = nullptr;
    } else {
      curr->next = l2;
      l2 = l2->next;
      curr = curr->next;
      curr->next = nullptr;
    }
  }

  if (l1 != nullptr) {
    curr->next = l1;
  } else {
    curr->next = l2;
  }

  return newList;
}

Node* mergeKLists(Node** lists, int k) {
  if (k == 0) {
    return nullptr;
  }

  if ( k == 1) {
    return lists[0];
  }


  while (k > 1) {
    int j = 0;
    for (int i = 0; i < k; i += 2) {
      if (i + 1 < k) {
        lists[j] = mergeTwoLists(lists[i], lists[i + 1]);
      } else {
        lists[j] = lists[i];
      }
      j++;
    }
    k = j;
  }

  return lists[0];
}

// ========== Helpers ==========
Node* makeList(std::vector<int> vals) {
  if (vals.empty()) return nullptr;
  Node* head = new Node{vals[0], nullptr};
  Node* curr = head;
  for (size_t i = 1; i < vals.size(); ++i) {
    curr->next = new Node{vals[i], nullptr};
    curr = curr->next;
  }
  return head;
}

std::vector<int> toVector(const Node* head) {
  std::vector<int> result;
  for (const Node* curr = head; curr != nullptr; curr = curr->next) {
    result.push_back(curr->data);
  }
  return result;
}

void assertSorted(const Node* head) {
  for (const Node* curr = head; curr != nullptr && curr->next != nullptr; curr = curr->next) {
    TestBase::assertTrue(curr->data <= curr->next->data);
  }
}

// ========== Tests ==========
TEST(MergeKSortedList_ListOf5) {
  Node* lists[] = {
    makeList({1, 3, 5}),
    makeList({2, 4, 6}),
    makeList({0, 7, 8}),
    makeList({9, 10, 11}),
    makeList({12, 13, 14})
  };

  const Node* merged = mergeKLists(lists, 5);
  assertSorted(merged);
  TestBase::assertVectorEqual(
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
    toVector(merged)
  );
}

TEST(MergeKSortedList_EmptyInput) {
  Node* result = mergeKLists(nullptr, 0);
  TestBase::assertTrue(result == nullptr);
}

TEST(MergeKSortedList_SingleList) {
  Node* lists[] = { makeList({1, 2, 3}) };
  const Node* merged = mergeKLists(lists, 1);
  TestBase::assertVectorEqual({1, 2, 3}, toVector(merged));
}

TEST(MergeKSortedList_TwoLists) {
  Node* lists[] = {
    makeList({1, 4, 7}),
    makeList({2, 5, 8})
  };

  const Node* merged = mergeKLists(lists, 2);
  assertSorted(merged);
  TestBase::assertVectorEqual({1, 2, 4, 5, 7, 8}, toVector(merged));
}

TEST(MergeKSortedList_WithDuplicates) {
  Node* lists[] = {
    makeList({1, 3, 5}),
    makeList({1, 3, 5}),
    makeList({2, 3, 4})
  };

  const Node* merged = mergeKLists(lists, 3);
  assertSorted(merged);
  TestBase::assertVectorEqual({1, 1, 2, 3, 3, 3, 4, 5, 5}, toVector(merged));
}

TEST(MergeKSortedList_DifferentLengths) {
  Node* lists[] = {
    makeList({1}),
    makeList({2, 4, 6, 8, 10}),
    makeList({3, 7})
  };

  const Node* merged = mergeKLists(lists, 3);
  assertSorted(merged);
  TestBase::assertVectorEqual({1, 2, 3, 4, 6, 7, 8, 10}, toVector(merged));
}

TEST(MergeKSortedList_SingleElementLists) {
  Node* lists[] = {
    makeList({5}),
    makeList({1}),
    makeList({3}),
    makeList({2})
  };

  const Node* merged = mergeKLists(lists, 4);
  assertSorted(merged);
  TestBase::assertVectorEqual({1, 2, 3, 5}, toVector(merged));
}

TEST(MergeKSortedList_NegativeValues) {
  Node* lists[] = {
    makeList({-10, -5, 0}),
    makeList({-7, -3, 4}),
    makeList({-1, 2, 6})
  };

  const Node* merged = mergeKLists(lists, 3);
  assertSorted(merged);
  TestBase::assertVectorEqual({-10, -7, -5, -3, -1, 0, 2, 4, 6}, toVector(merged));
}

TEST(MergeKSortedList_AllSameValues) {
  Node* lists[] = {
    makeList({5, 5, 5}),
    makeList({5, 5}),
    makeList({5})
  };

  const Node* merged = mergeKLists(lists, 3);
  assertSorted(merged);
  TestBase::assertVectorEqual({5, 5, 5, 5, 5, 5}, toVector(merged));
}

} // namespace MergeKSortedList
