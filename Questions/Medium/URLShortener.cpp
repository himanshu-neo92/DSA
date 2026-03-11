/*
Problem: URL Shortener Service
Shorten URLs and retrieve the original URL via short code.

Approach:
- Use hash maps to map short codes to long URLs and vice versa
- Generate unique base-62 codes from an incrementing counter
- Return existing short code if URL was already shortened

==================== PERFORMANCE ====================
Time Complexity:  O(L) per shorten/retrieve where L = code length
Space Complexity: O(n) where n = number of URLs stored
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <string>

namespace URLShortener {

class URLShortenerSystem {
public:
    // TODO: implement shorten and retrieve
    std::string shorten(const std::string& longUrl) {
        return "";
    }

    std::string retrieve(const std::string& shortCode) {
        return "";
    }

private:
    std::unordered_map<std::string, std::string> shortToLong;
    std::unordered_map<std::string, std::string> longToShort;
    int counter = 0;

    std::string encode(int num) {
        return "";
    }
};

// ========== Tests ==========

TEST(URLShortener_ShortenAndRetrieve) {
    URLShortenerSystem us;
    std::string code = us.shorten("https://www.example.com/very/long/path");
    TestBase::assertTrue(!code.empty(), "Should return non-empty code");
    std::string retrieved = us.retrieve(code);
    TestBase::assertTrue(retrieved == "https://www.example.com/very/long/path", "Should retrieve original");
}

TEST(URLShortener_SameUrlSameCode) {
    URLShortenerSystem us;
    std::string code1 = us.shorten("https://example.com");
    std::string code2 = us.shorten("https://example.com");
    TestBase::assertTrue(code1 == code2, "Same URL should produce same code");
}

TEST(URLShortener_DifferentUrlsDifferentCodes) {
    URLShortenerSystem us;
    std::string code1 = us.shorten("https://example.com/a");
    std::string code2 = us.shorten("https://example.com/b");
    TestBase::assertTrue(code1 != code2, "Different URLs should get different codes");
}

TEST(URLShortener_RetrieveNonExistent) {
    URLShortenerSystem us;
    std::string result = us.retrieve("nonexistent");
    TestBase::assertTrue(result.empty(), "Should return empty for unknown code");
}

TEST(URLShortener_MultipleUrls) {
    URLShortenerSystem us;
    std::string c1 = us.shorten("https://a.com");
    std::string c2 = us.shorten("https://b.com");
    std::string c3 = us.shorten("https://c.com");

    TestBase::assertTrue(us.retrieve(c1) == "https://a.com", "Retrieve first");
    TestBase::assertTrue(us.retrieve(c2) == "https://b.com", "Retrieve second");
    TestBase::assertTrue(us.retrieve(c3) == "https://c.com", "Retrieve third");
}

} // namespace URLShortener
