// Problem: Longest Palindromic Substring
// Given a string s, return the longest palindromic substring.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n²) - Expand around each center
// Space Complexity: O(1) - Only indices tracked
//
// Key concepts:
// - Palindrome can be odd-length (single center) or even-length (two centers)
// - Expand outward from each possible center
// - Track the longest found
// =======================================================

#include "TestBase.h"

namespace LongestPalindromicString {

// ========== Solution ==========
std::string longestPalindrome(const std::string& s) {
    // TODO: implement your solution here
    return "";
}

// ========== Tests ==========

TEST(LongestPalindrome_Basic) {
    std::string result = longestPalindrome("babad");
    TestBase::assertTrue(result == "bab" || result == "aba", "Expected bab or aba");
}

TEST(LongestPalindrome_Even) {
    TestBase::assertTrue(longestPalindrome("cbbd") == "bb", "Expected bb");
}

TEST(LongestPalindrome_Single) {
    TestBase::assertTrue(longestPalindrome("a") == "a", "Single char");
}

TEST(LongestPalindrome_AllSame) {
    TestBase::assertTrue(longestPalindrome("aaaa") == "aaaa", "All same chars");
}

TEST(LongestPalindrome_Whole) {
    TestBase::assertTrue(longestPalindrome("racecar") == "racecar", "Whole string palindrome");
}

TEST(LongestPalindrome_NoPalindromeGt1) {
    std::string result = longestPalindrome("abcde");
    TestBase::assertEqual(1, (int)result.size());
}

TEST(LongestPalindrome_Empty) {
    TestBase::assertTrue(longestPalindrome("") == "", "Empty string");
}

} // namespace LongestPalindromicString
