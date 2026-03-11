/*
Problem: Online Stock Span
Write an algorithm that collects daily price quotes from some stock
and returns the span of that stock price for the current day.
The span is the count of consecutive days (including today) for which
the stock's price was <= today's price.

Example: [7,1,2,2] and today is 3 → span is 4

==================== PERFORMANCE ====================
Time Complexity:  O(1) amortized per call to next()
Space Complexity: O(n) - monotonic stack

Key concepts:
- Monotonic decreasing stack
- Each element stores (price, span)
- When a new price comes in, pop all smaller prices and accumulate their spans
=======================================================
*/

#include "TestBase.h"

namespace OnlineStockSpan {

class StockSpan {
public:
    StockSpan() {}
    ~StockSpan() {}

    int next(int price) {
        // TODO: implement using monotonic stack
        return 0;
    }

private:
    struct data {
        int price;
        int span;
    };
    std::stack<data> st;
};

// ========== Tests ==========
TEST(StockSpan_Base) {
    OnlineStockSpan::StockSpan* obj = new OnlineStockSpan::StockSpan();
    TestBase::assertEqual(1, obj->next(100));
    TestBase::assertEqual(1, obj->next(80));
    TestBase::assertEqual(1, obj->next(60));
    TestBase::assertEqual(2, obj->next(70));
    TestBase::assertEqual(1, obj->next(50));
    TestBase::assertEqual(5, obj->next(85));
    TestBase::assertEqual(1, obj->next(20));
    TestBase::assertEqual(2, obj->next(80));
    TestBase::assertEqual(1, obj->next(70));
    TestBase::assertEqual(4, obj->next(85));
    delete obj;
}

} // namespace OnlineStockSpan
