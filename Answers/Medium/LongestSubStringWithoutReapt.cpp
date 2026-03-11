// Problem: Longest Substring Without Repeating Characters (LeetCode 3)
// Given a string, find the length of the longest substring without repeating chars.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Sliding window
// Space Complexity: O(min(n, alphabet)) - Hash set or array for window
//
// Key concepts:
// - Sliding window with two pointers (left, right)
// - Expand right; if duplicate found, shrink left until no duplicates
// - Track maximum window size
// =======================================================

#include "TestBase.h"
#include <unordered_set>

namespace LongestSubStringWithoutRepeat {

// ========== Solution ==========
int lengthOfLongestSubstring(const std::string& s) {
    std::unordered_set<char> window;
    int maxLen = 0;
    int left = 0;

    for (int right = 0; right < (int)s.size(); ++right) {
        while (window.count(s[right])) {
            window.erase(s[left]);
            ++left;
        }
        window.insert(s[right]);
        maxLen = std::max(maxLen, right - left + 1);
    }

    return maxLen;
}

// ========== Tests ==========

TEST(LongestSubStr_Basic) {
    TestBase::assertEqual(3, lengthOfLongestSubstring("abcabcbb"));
}

TEST(LongestSubStr_AllSame) {
    TestBase::assertEqual(1, lengthOfLongestSubstring("bbbbb"));
}

TEST(LongestSubStr_Mixed) {
    TestBase::assertEqual(3, lengthOfLongestSubstring("pwwkew"));
}

TEST(LongestSubStr_Empty) {
    TestBase::assertEqual(0, lengthOfLongestSubstring(""));
}

TEST(LongestSubStr_Single) {
    TestBase::assertEqual(1, lengthOfLongestSubstring("a"));
}

TEST(LongestSubStr_AllUnique) {
    TestBase::assertEqual(5, lengthOfLongestSubstring("abcde"));
}

TEST(LongestSubStr_TwoChars) {
    TestBase::assertEqual(2, lengthOfLongestSubstring("au"));
}

TEST(LongestSubStr_RepeatAtEnd) {
    TestBase::assertEqual(3, lengthOfLongestSubstring("dvdf"));
}

} // namespace LongestSubStringWithoutRepeat
