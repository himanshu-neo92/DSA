/*
Problem: Real-Time Stock Price Tracker
Track stock prices in real time and support current/minimum/maximum price queries.

Approach:
- Use a hash map for latest price at each timestamp
- Use a multiset for fast min/max queries
- Track the latest timestamp for current price

==================== PERFORMANCE ====================
Time Complexity:  O(log n) per update, O(1) for current/min/max
Space Complexity: O(n) where n = number of updates
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <set>

namespace StockPriceTracker {

class StockTracker {
public:
    // TODO: implement update, current, maximum, minimum
    void update(int timestamp, int price) {}

    int current() { return 0; }
    int maximum() { return 0; }
    int minimum() { return 0; }

private:
    std::unordered_map<int, int> timestampPrice;
    std::multiset<int> prices;
    int latestTimestamp = 0;
};

// ========== Tests ==========

TEST(StockTracker_BasicUpdate) {
    StockTracker st;
    st.update(1, 100);
    TestBase::assertEqual(100, st.current());
    TestBase::assertEqual(100, st.maximum());
    TestBase::assertEqual(100, st.minimum());
}

TEST(StockTracker_MultipleUpdates) {
    StockTracker st;
    st.update(1, 100);
    st.update(2, 200);
    st.update(3, 150);

    TestBase::assertEqual(150, st.current());
    TestBase::assertEqual(200, st.maximum());
    TestBase::assertEqual(100, st.minimum());
}

TEST(StockTracker_CorrectionUpdate) {
    StockTracker st;
    st.update(1, 100);
    st.update(2, 200);
    st.update(1, 50);

    TestBase::assertEqual(200, st.current());
    TestBase::assertEqual(200, st.maximum());
    TestBase::assertEqual(50, st.minimum());
}

TEST(StockTracker_LatestTimestamp) {
    StockTracker st;
    st.update(3, 300);
    st.update(1, 100);
    st.update(2, 200);

    TestBase::assertEqual(300, st.current());
}

TEST(StockTracker_AllSamePrice) {
    StockTracker st;
    st.update(1, 50);
    st.update(2, 50);
    st.update(3, 50);

    TestBase::assertEqual(50, st.current());
    TestBase::assertEqual(50, st.maximum());
    TestBase::assertEqual(50, st.minimum());
}

TEST(StockTracker_CorrectionChangesMinMax) {
    StockTracker st;
    st.update(1, 10);
    st.update(2, 20);
    TestBase::assertEqual(10, st.minimum());

    st.update(1, 25);
    TestBase::assertEqual(20, st.minimum());
    TestBase::assertEqual(25, st.maximum());
}

TEST(StockTracker_SingleUpdate) {
    StockTracker st;
    st.update(42, 999);
    TestBase::assertEqual(999, st.current());
    TestBase::assertEqual(999, st.maximum());
    TestBase::assertEqual(999, st.minimum());
}

} // namespace StockPriceTracker
