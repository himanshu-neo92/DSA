/*
Problem: Spam Filter (Detecting Duplicate Messages in a Time Window)
Detect if a message is a duplicate within a recent time window (e.g., 10 seconds).

Approach:
- Use a hash map for message timestamps
- Use a queue for message order to expire old entries
- A message is spam if it was seen within the window

==================== PERFORMANCE ====================
Time Complexity:  O(1) amortized per isDuplicate call
Space Complexity: O(n) where n = messages in current window
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <queue>
#include <string>

namespace SpamFilter {

class SpamFilterSystem {
public:
    // TODO: implement constructor and isDuplicate
    SpamFilterSystem(int window) : window(window) {}

    bool isDuplicate(const std::string& msg, int timestamp) {
        return false;
    }

private:
    std::unordered_map<std::string, int> lastSeen;
    std::queue<std::pair<std::string, int>> msgQueue;
    int window;
};

// ========== Tests ==========

TEST(SpamFilter_FirstMessageNotSpam) {
    SpamFilterSystem sf(10);
    TestBase::assertFalse(sf.isDuplicate("hello", 1), "First message not spam");
}

TEST(SpamFilter_DuplicateInWindow) {
    SpamFilterSystem sf(10);
    TestBase::assertFalse(sf.isDuplicate("hello", 1), "First ok");
    TestBase::assertTrue(sf.isDuplicate("hello", 5), "Duplicate within window");
}

TEST(SpamFilter_DuplicateAfterWindow) {
    SpamFilterSystem sf(5);
    TestBase::assertFalse(sf.isDuplicate("hello", 1), "First ok");
    TestBase::assertFalse(sf.isDuplicate("hello", 7), "After window expired");
}

TEST(SpamFilter_DifferentMessages) {
    SpamFilterSystem sf(10);
    TestBase::assertFalse(sf.isDuplicate("hello", 1), "First message");
    TestBase::assertFalse(sf.isDuplicate("world", 2), "Different message");
}

TEST(SpamFilter_ExactWindowBoundary) {
    SpamFilterSystem sf(5);
    TestBase::assertFalse(sf.isDuplicate("msg", 0), "First");
    TestBase::assertTrue(sf.isDuplicate("msg", 5), "At exact boundary still in window");
    TestBase::assertFalse(sf.isDuplicate("msg", 6), "Just past boundary");
}

TEST(SpamFilter_MultipleMessagesExpire) {
    SpamFilterSystem sf(3);
    TestBase::assertFalse(sf.isDuplicate("a", 1), "a at 1");
    TestBase::assertFalse(sf.isDuplicate("b", 2), "b at 2");
    TestBase::assertFalse(sf.isDuplicate("c", 3), "c at 3");
    TestBase::assertFalse(sf.isDuplicate("a", 5), "a at 5 (expired)");
    TestBase::assertTrue(sf.isDuplicate("b", 5), "b at 5 (still in window)");
}

TEST(SpamFilter_RapidDuplicates) {
    SpamFilterSystem sf(10);
    TestBase::assertFalse(sf.isDuplicate("spam", 1), "First ok");
    TestBase::assertTrue(sf.isDuplicate("spam", 1), "Immediate duplicate");
    TestBase::assertTrue(sf.isDuplicate("spam", 2), "Still duplicate");
}

} // namespace SpamFilter
