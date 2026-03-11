/*
Problem: Median Finder in Streaming Data
Continuously add numbers and return the median at any time.

Approach:
- Use two heaps: max-heap for lower half and min-heap for upper half
- Balance the heaps so their sizes differ by at most 1
- Median is top of max-heap (odd count) or average of both tops (even count)

==================== PERFORMANCE ====================
Time Complexity:  O(log n) per addNum, O(1) per findMedian
Space Complexity: O(n)
=======================================================
*/

#include "TestBase.h"
#include <queue>

namespace MedianFinder {

class MedianFinderSystem {
public:
    // TODO: implement addNum and findMedian
    void addNum(int num) {}

    double findMedian() {
        return 0.0;
    }

private:
    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};

// ========== Tests ==========

TEST(MedianFinder_SingleElement) {
    MedianFinderSystem mf;
    mf.addNum(5);
    TestBase::assertTrue(mf.findMedian() == 5.0, "Single element median");
}

TEST(MedianFinder_TwoElements) {
    MedianFinderSystem mf;
    mf.addNum(1);
    mf.addNum(2);
    TestBase::assertTrue(mf.findMedian() == 1.5, "Median of 1 and 2");
}

TEST(MedianFinder_OddCount) {
    MedianFinderSystem mf;
    mf.addNum(1);
    mf.addNum(2);
    mf.addNum(3);
    TestBase::assertTrue(mf.findMedian() == 2.0, "Median of 1,2,3");
}

TEST(MedianFinder_EvenCount) {
    MedianFinderSystem mf;
    mf.addNum(1);
    mf.addNum(2);
    mf.addNum(3);
    mf.addNum(4);
    TestBase::assertTrue(mf.findMedian() == 2.5, "Median of 1,2,3,4");
}

TEST(MedianFinder_UnsortedInput) {
    MedianFinderSystem mf;
    mf.addNum(5);
    mf.addNum(2);
    mf.addNum(8);
    mf.addNum(1);
    mf.addNum(3);
    TestBase::assertTrue(mf.findMedian() == 3.0, "Median of unsorted 5,2,8,1,3");
}

TEST(MedianFinder_Duplicates) {
    MedianFinderSystem mf;
    mf.addNum(5);
    mf.addNum(5);
    mf.addNum(5);
    TestBase::assertTrue(mf.findMedian() == 5.0, "All duplicates");
}

TEST(MedianFinder_NegativeNumbers) {
    MedianFinderSystem mf;
    mf.addNum(-1);
    mf.addNum(-2);
    mf.addNum(-3);
    TestBase::assertTrue(mf.findMedian() == -2.0, "Negative numbers");
}

TEST(MedianFinder_StreamingUpdates) {
    MedianFinderSystem mf;
    mf.addNum(1);
    TestBase::assertTrue(mf.findMedian() == 1.0, "After 1");
    mf.addNum(2);
    TestBase::assertTrue(mf.findMedian() == 1.5, "After 1,2");
    mf.addNum(3);
    TestBase::assertTrue(mf.findMedian() == 2.0, "After 1,2,3");
}

} // namespace MedianFinder
