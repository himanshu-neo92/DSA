// Problem: Welsh Dictionary (Hard variant)
// Sort words according to the Welsh alphabet and support lookup/insertion
// into a sorted dictionary structure with prefix search.
//
// Welsh Alphabet Order:
// a, b, c, ch, d, dd, e, f, ff, g, ng, h, i, j, l, ll, m, n, o, p, ph, r, rh, s, t, th, u, w, y
//
// Required operations:
// 1. Tokenize words into Welsh alphabet units
// 2. Insert into sorted dictionary (binary search insertion)
// 3. Lookup (contains)
// 4. Prefix search (find all words starting with a Welsh token)
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(k log n) per insert/lookup
// Space Complexity: O(n * k) for the sorted dictionary
// =======================================================

#include "TestBase.h"
#include <unordered_map>
#include <algorithm>

namespace WelshDictHard {

class WelshDictionary {
private:
    std::unordered_map<std::string, int> letterOrder;
    std::vector<std::string> alphabet = {
        "a", "b", "c", "ch", "d", "dd", "e", "f", "ff", "g", "ng", "h",
        "i", "j", "l", "ll", "m", "n", "o", "p", "ph", "r", "rh", "s",
        "t", "th", "u", "w", "y"
    };
    std::vector<std::string> sortedWords;

public:
    WelshDictionary() {
        for (int i = 0; i < (int)alphabet.size(); i++) {
            letterOrder[alphabet[i]] = i;
        }
    }

    // TODO: implement tokenize
    std::vector<std::string> tokenize(const std::string& word) { return {}; }

    // TODO: implement compare (-1, 0, 1)
    int compare(const std::string& a, const std::string& b) { return 0; }

    // TODO: implement insert (maintain sorted order)
    void insert(const std::string& word) {}

    // TODO: implement contains (binary search)
    bool contains(const std::string& word) { return false; }

    // TODO: implement prefix search
    std::vector<std::string> prefixSearch(const std::string& prefix) { return {}; }

    const std::vector<std::string>& getWords() const { return sortedWords; }
};

// ========== Tests ==========

TEST(WelshDictHard_InsertAndContains) {
    WelshDictionary dict;
    dict.insert("cyllell");
    dict.insert("ci");
    dict.insert("chwaer");
    TestBase::assertTrue(dict.contains("ci"), "Should find ci");
    TestBase::assertTrue(dict.contains("chwaer"), "Should find chwaer");
    TestBase::assertFalse(dict.contains("xyz"), "Should not find xyz");
}

TEST(WelshDictHard_SortedOrder) {
    WelshDictionary dict;
    dict.insert("chwaer");
    dict.insert("ci");
    dict.insert("cacen");
    auto words = dict.getWords();
    TestBase::assertTrue(words[0] == "cacen", "First should be cacen");
    TestBase::assertTrue(words[1] == "ci", "Second should be ci");
    TestBase::assertTrue(words[2] == "chwaer", "Third should be chwaer");
}

TEST(WelshDictHard_PrefixSearch) {
    WelshDictionary dict;
    dict.insert("cacen");
    dict.insert("car");
    dict.insert("ci");
    dict.insert("chwaer");
    dict.insert("draig");
    auto results = dict.prefixSearch("c");
    TestBase::assertEqual(3, (int)results.size());
}

TEST(WelshDictHard_DigraphOrder) {
    WelshDictionary dict;
    dict.insert("dydd");
    dict.insert("chwaer");
    dict.insert("car");
    auto words = dict.getWords();
    TestBase::assertTrue(words[0] == "car", "c before ch");
    TestBase::assertTrue(words[1] == "chwaer", "ch before d");
    TestBase::assertTrue(words[2] == "dydd", "d last");
}

TEST(WelshDictHard_EmptyDict) {
    WelshDictionary dict;
    TestBase::assertFalse(dict.contains("anything"), "Empty dict contains nothing");
    TestBase::assertEqual(0, (int)dict.prefixSearch("a").size());
}

} // namespace WelshDictHard
