// Problem: Online Stock Span
// Collect daily price quotes and return the span for the current day,
// i.e., the count of consecutive days where price was <= today's price.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(1) amortized per call - each element pushed/popped at most once
// Space Complexity: O(n) - monotonic stack holds at most n entries
//
// Key concepts:
// - Monotonic decreasing stack storing (price, span) pairs
// - Pop smaller elements and accumulate their spans
// =======================================================

#include "TestBase.h"

namespace OnlineStockSpan {

  class StockSpan {
    public:
    StockSpan() {}
    ~StockSpan() {}

    int next(int price) {
      int currSpan = 1;

      // We maintain this stack as a monotonic stack, we only push if the element is > the current top
      // other wise we pop the top and add the span for that top to the current span.
      while (!st.empty() && st.top().price < price ) {
        currSpan += st.top().span;
        st.pop();
      }

      st.push({price, currSpan});

      return currSpan;

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
TestBase::assertEqual(1 ,obj->next(100));
TestBase::assertEqual(1 ,obj->next(80));
TestBase::assertEqual(1 ,obj->next(60));
TestBase::assertEqual(2 ,obj->next(70));
TestBase::assertEqual(1 ,obj->next(50));
TestBase::assertEqual(5 ,obj->next(85));
TestBase::assertEqual(1 ,obj->next(20));
TestBase::assertEqual(2 ,obj->next(80));
TestBase::assertEqual(1 ,obj->next(70));
TestBase::assertEqual(4 ,obj->next(85));
}

TEST(StockSpan_SingleElement) {
  OnlineStockSpan::StockSpan obj;
  TestBase::assertEqual(1, obj.next(42), "Single element span should be 1");
}

TEST(StockSpan_AllIncreasing) {
  OnlineStockSpan::StockSpan obj;
  TestBase::assertEqual(1, obj.next(10), "First element");
  TestBase::assertEqual(2, obj.next(20), "20 > 10, span = 2");
  TestBase::assertEqual(3, obj.next(30), "30 > 20 > 10, span = 3");
  TestBase::assertEqual(4, obj.next(40), "40 > 30 > 20 > 10, span = 4");
  TestBase::assertEqual(5, obj.next(50), "50 > all previous, span = 5");
}

TEST(StockSpan_AllDecreasing) {
  OnlineStockSpan::StockSpan obj;
  TestBase::assertEqual(1, obj.next(50), "First element");
  TestBase::assertEqual(1, obj.next(40), "40 < 50, span = 1");
  TestBase::assertEqual(1, obj.next(30), "30 < 40, span = 1");
  TestBase::assertEqual(1, obj.next(20), "20 < 30, span = 1");
  TestBase::assertEqual(1, obj.next(10), "10 < 20, span = 1");
}

TEST(StockSpan_AllEqual) {
  OnlineStockSpan::StockSpan obj;
  TestBase::assertEqual(1, obj.next(5), "First element");
  TestBase::assertEqual(1, obj.next(5), "Equal not strictly less, span = 1");
  TestBase::assertEqual(1, obj.next(5), "Still equal, span = 1");
}



} // namespace OnlineStockSpan
