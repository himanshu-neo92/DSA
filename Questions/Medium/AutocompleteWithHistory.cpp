/*
Problem: Autocomplete with Recent History Bias
Suggest autocomplete results prioritizing recently used words.

Approach:
- Use a list to maintain recently used words (most recent first)
- Use a hash map for word frequency
- Suggestions come from the recent list, filtered by prefix

==================== PERFORMANCE ====================
Time Complexity:  O(R) per suggest where R = recent list size, O(R) per useWord
Space Complexity: O(R + W) where R = max recent, W = unique words
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <list>
#include <string>
#include <vector>

namespace AutocompleteWithHistory {

class AutocompleteHistory {
public:
    // TODO: implement useWord and suggest
    AutocompleteHistory(int maxRecent) : maxRecent(maxRecent) {}

    void useWord(const std::string& word) {}

    std::vector<std::string> suggest(const std::string& prefix) {
        return {};
    }

private:
    std::unordered_map<std::string, int> freq;
    std::list<std::string> recent;
    int maxRecent;
};

// ========== Tests ==========

TEST(AutocompleteHistory_BasicSuggest) {
    AutocompleteHistory ac(5);
    ac.useWord("apple");
    ac.useWord("application");
    ac.useWord("banana");

    auto result = ac.suggest("app");
    TestBase::assertEqual(2, (int)result.size());
    TestBase::assertTrue(result[0] == "application", "Most recent first");
    TestBase::assertTrue(result[1] == "apple", "Older second");
}

TEST(AutocompleteHistory_RecentOrder) {
    AutocompleteHistory ac(5);
    ac.useWord("apple");
    ac.useWord("app");
    ac.useWord("apple");

    auto result = ac.suggest("app");
    TestBase::assertTrue(result[0] == "apple", "apple most recently used");
}

TEST(AutocompleteHistory_NoMatch) {
    AutocompleteHistory ac(5);
    ac.useWord("hello");

    auto result = ac.suggest("xyz");
    TestBase::assertEqual(0, (int)result.size());
}

TEST(AutocompleteHistory_MaxRecentEviction) {
    AutocompleteHistory ac(2);
    ac.useWord("a1");
    ac.useWord("a2");
    ac.useWord("a3");

    auto result = ac.suggest("a");
    TestBase::assertEqual(2, (int)result.size());
    TestBase::assertTrue(result[0] == "a3", "Most recent");
    TestBase::assertTrue(result[1] == "a2", "Second recent");
}

TEST(AutocompleteHistory_EmptyHistory) {
    AutocompleteHistory ac(5);
    auto result = ac.suggest("test");
    TestBase::assertEqual(0, (int)result.size());
}

TEST(AutocompleteHistory_PrefixMatchAll) {
    AutocompleteHistory ac(10);
    ac.useWord("test");
    ac.useWord("testing");
    ac.useWord("tested");

    auto result = ac.suggest("test");
    TestBase::assertEqual(3, (int)result.size());
}

} // namespace AutocompleteWithHistory
