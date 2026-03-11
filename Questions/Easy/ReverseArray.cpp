// Problem: Reverse Array
// Reverse an array in-place
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) - Processes n/2 swaps
// Space Complexity: O(1) - In-place, only uses two pointers
//
// Alternative approaches:
// - std::reverse(): O(n) time, O(1) space - Same complexity, more readable
// - Create new reversed array: O(n) time, O(n) space - Wastes memory
// - Recursive: O(n) time, O(n) space - Stack overhead, not recommended
//
// Why this approach is optimal:
// - In-place means no extra memory allocation
// - Two-pointer technique is cache-friendly (sequential access from both ends)
// - std::swap is optimized by compiler (often uses XOR or move semantics)
//
// Cache considerations:
// - Good spatial locality at start, degrades as pointers converge
// - For very large arrays, consider cache-oblivious algorithms
// - Modern CPUs prefetch well for this access pattern
// =======================================================

#include "TestBase.h"
#include <vector>
#include <algorithm>

namespace ReverseArray {

// ========== Solution ==========
void reverseArray(std::vector<int>& arr) {
    // TODO: implement your solution here
}

// ========== Tests ==========
TEST(ReverseArray_OddLength) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    reverseArray(arr);
    TestBase::assertVectorEqual({5, 4, 3, 2, 1}, arr);
}

TEST(ReverseArray_EvenLength) {
    std::vector<int> arr = {1, 2, 3, 4};
    reverseArray(arr);
    TestBase::assertVectorEqual({4, 3, 2, 1}, arr);
}

TEST(ReverseArray_SingleElement) {
    std::vector<int> arr = {42};
    reverseArray(arr);
    TestBase::assertVectorEqual({42}, arr);
}

} // namespace ReverseArray
