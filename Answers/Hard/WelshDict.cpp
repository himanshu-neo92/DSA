// Problem: Welsh Dictionary (Hard variant)
// Sort words according to the Welsh alphabet and support lookup/insertion
// into a sorted dictionary structure.
//
// Welsh Alphabet Order:
// a, b, c, ch, d, dd, e, f, ff, g, ng, h, i, j, l, ll, m, n, o, p, ph, r, rh, s, t, th, u, w, y
//
// This hard variant requires:
// 1. Tokenization of words into Welsh alphabet units
// 2. Custom comparison
// 3. Binary search insertion into a sorted dictionary
// 4. Prefix search (find all words starting with a Welsh token)
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(k log n) per insert/lookup where k = word length, n = dict size
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

    std::vector<std::string> tokenize(const std::string& word) {
        std::vector<std::string> tokens;
        int i = 0, n = word.size();
        while (i < n) {
            if (i + 1 < n) {
                std::string digraph = word.substr(i, 2);
                if (letterOrder.count(digraph)) {
                    tokens.push_back(digraph);
                    i += 2;
                    continue;
                }
            }
            tokens.push_back(word.substr(i, 1));
            i++;
        }
        return tokens;
    }

    int compare(const std::string& a, const std::string& b) {
        auto ta = tokenize(a);
        auto tb = tokenize(b);
        int minLen = std::min(ta.size(), tb.size());

        for (int i = 0; i < minLen; i++) {
            int oa = letterOrder.count(ta[i]) ? letterOrder[ta[i]] : -1;
            int ob = letterOrder.count(tb[i]) ? letterOrder[tb[i]] : -1;
            if (oa != ob) return (oa < ob) ? -1 : 1;
        }

        if (ta.size() == tb.size()) return 0;
        return (ta.size() < tb.size()) ? -1 : 1;
    }

    void insert(const std::string& word) {
        auto it = std::lower_bound(sortedWords.begin(), sortedWords.end(), word,
            [this](const std::string& a, const std::string& b) {
                return compare(a, b) < 0;
            });
        sortedWords.insert(it, word);
    }

    bool contains(const std::string& word) {
        auto it = std::lower_bound(sortedWords.begin(), sortedWords.end(), word,
            [this](const std::string& a, const std::string& b) {
                return compare(a, b) < 0;
            });
        return it != sortedWords.end() && compare(*it, word) == 0;
    }

    std::vector<std::string> prefixSearch(const std::string& prefix) {
        auto prefixTokens = tokenize(prefix);
        std::vector<std::string> result;
        for (const auto& word : sortedWords) {
            auto wordTokens = tokenize(word);
            if (wordTokens.size() >= prefixTokens.size()) {
                bool match = true;
                for (size_t i = 0; i < prefixTokens.size(); i++) {
                    if (wordTokens[i] != prefixTokens[i]) { match = false; break; }
                }
                if (match) result.push_back(word);
            }
        }
        return result;
    }

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
    // c < ch < d in Welsh
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
