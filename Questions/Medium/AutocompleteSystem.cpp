/*
Problem: Autocomplete System (Word Prediction)
Design a word prediction system that, given a prefix, returns the top-k
most frequent words starting with that prefix.

Approach:
- Utilize a Trie for efficient prefix searching
- Maintain a frequency map at each trie node for words passing through it
- Use a min-heap (priority queue) to retrieve the top-k frequent matches

==================== PERFORMANCE ====================
Time Complexity:  O(p + n log k) where p = prefix length, n = words with prefix
Space Complexity: O(W * L) where W = total words, L = avg word length
=======================================================
*/

#include "TestBase.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

namespace AutocompleteSystem {

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    std::unordered_map<std::string, int> wordFreq;
};

class Autocomplete {
public:
    Autocomplete() { root = new TrieNode(); }

    // TODO: implement insert and predict
    void insert(const std::string& word, int freq) {}

    std::vector<std::string> predict(const std::string& prefix, int k) {
        return {};
    }

private:
    TrieNode* root;
};

// ========== Tests ==========

TEST(Autocomplete_BasicPredict) {
    Autocomplete ac;
    ac.insert("apple", 5);
    ac.insert("app", 3);
    ac.insert("application", 2);
    ac.insert("banana", 4);

    auto result = ac.predict("app", 2);
    TestBase::assertEqual(2, (int)result.size());
    TestBase::assertTrue(result[0] == "apple", "Top result should be apple");
    TestBase::assertTrue(result[1] == "app", "Second result should be app");
}

TEST(Autocomplete_NoMatch) {
    Autocomplete ac;
    ac.insert("hello", 1);
    ac.insert("help", 2);

    auto result = ac.predict("xyz", 3);
    TestBase::assertEqual(0, (int)result.size());
}

TEST(Autocomplete_SingleMatch) {
    Autocomplete ac;
    ac.insert("unique", 10);
    ac.insert("other", 5);

    auto result = ac.predict("uni", 5);
    TestBase::assertEqual(1, (int)result.size());
    TestBase::assertTrue(result[0] == "unique", "Should find unique");
}

TEST(Autocomplete_KLargerThanResults) {
    Autocomplete ac;
    ac.insert("cat", 3);
    ac.insert("car", 5);

    auto result = ac.predict("ca", 10);
    TestBase::assertEqual(2, (int)result.size());
    TestBase::assertTrue(result[0] == "car", "car has higher freq");
}

TEST(Autocomplete_ExactWordAsPrefix) {
    Autocomplete ac;
    ac.insert("the", 10);
    ac.insert("them", 5);
    ac.insert("there", 3);

    auto result = ac.predict("the", 3);
    TestBase::assertEqual(3, (int)result.size());
    TestBase::assertTrue(result[0] == "the", "Exact match with highest freq first");
}

TEST(Autocomplete_EmptyPrefix) {
    Autocomplete ac;
    ac.insert("a", 1);
    ac.insert("b", 2);
    ac.insert("c", 3);

    auto result = ac.predict("", 2);
    TestBase::assertEqual(2, (int)result.size());
    TestBase::assertTrue(result[0] == "c", "Highest freq first");
}

TEST(Autocomplete_UpdateFrequency) {
    Autocomplete ac;
    ac.insert("test", 1);
    ac.insert("test", 5);

    auto result = ac.predict("te", 1);
    TestBase::assertEqual(1, (int)result.size());
    TestBase::assertTrue(result[0] == "test", "Should find test with accumulated freq");
}

} // namespace AutocompleteSystem
