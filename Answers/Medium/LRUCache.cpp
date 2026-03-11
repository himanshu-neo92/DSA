/*
Problem: LRU Cache (Least Recently Used Cache)
Design an LRU cache that supports fast get and put operations, evicting
the least recently accessed item when capacity is exceeded.

Approach:
- Use a doubly linked list to track order of usage
- Use a hash map for O(1) access to nodes
- On get/put, move node to front (most recently used)
- On capacity overflow, remove from tail (least recently used)

==================== PERFORMANCE ====================
Time Complexity:  O(1) for both get and put
Space Complexity: O(capacity)
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>

namespace LRUCacheNS {

struct Node {
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) return -1;
        Node* node = cache[key];
        remove(node);
        insert(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.count(key)) {
            remove(cache[key]);
            delete cache[key];
        }
        Node* node = new Node(key, value);
        insert(node);
        cache[key] = node;
        if ((int)cache.size() > capacity) {
            Node* toRemove = tail->prev;
            remove(toRemove);
            cache.erase(toRemove->key);
            delete toRemove;
        }
    }

private:
    int capacity;
    std::unordered_map<int, Node*> cache;
    Node *head, *tail;

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insert(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
};

// ========== Tests ==========

TEST(LRUCache_BasicGetPut) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    TestBase::assertEqual(1, cache.get(1));
    cache.put(3, 3);
    TestBase::assertEqual(-1, cache.get(2));
    TestBase::assertEqual(3, cache.get(3));
}

TEST(LRUCache_Eviction) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    TestBase::assertEqual(-1, cache.get(1));
    TestBase::assertEqual(2, cache.get(2));
    TestBase::assertEqual(3, cache.get(3));
}

TEST(LRUCache_UpdateExisting) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(1, 10);
    cache.put(3, 3);
    TestBase::assertEqual(10, cache.get(1));
    TestBase::assertEqual(-1, cache.get(2));
}

TEST(LRUCache_GetUpdatesRecency) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);
    cache.put(3, 3);
    TestBase::assertEqual(1, cache.get(1));
    TestBase::assertEqual(-1, cache.get(2));
}

TEST(LRUCache_MissReturnsNeg1) {
    LRUCache cache(1);
    TestBase::assertEqual(-1, cache.get(99));
}

TEST(LRUCache_SingleCapacity) {
    LRUCache cache(1);
    cache.put(1, 1);
    TestBase::assertEqual(1, cache.get(1));
    cache.put(2, 2);
    TestBase::assertEqual(-1, cache.get(1));
    TestBase::assertEqual(2, cache.get(2));
}

TEST(LRUCache_OverwriteSameKey) {
    LRUCache cache(2);
    cache.put(1, 100);
    cache.put(1, 200);
    TestBase::assertEqual(200, cache.get(1));
}

} // namespace LRUCacheNS
