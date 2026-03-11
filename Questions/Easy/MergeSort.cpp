// Problem: Merge Sort
// Implement the merge sort algorithm to sort an array in ascending order.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) - Divide array log(n) times, merge O(n) each
// Space Complexity: O(n) - Temporary arrays for merging
//
// Key concepts:
// - Divide and conquer: split array into halves, sort each, merge
// - Stable sort: preserves relative order of equal elements
// - mergeArray: merges two sorted subarrays arr[l..m] and arr[m+1..r]
// - mergerSort: recursively divides and sorts
// =======================================================

#include "TestBase.h"

namespace MergeSort {

// ========== Solution ==========
void mergeArray(int arr[], int l, int m, int r) {
    // TODO: implement merge of arr[l..m] and arr[m+1..r]
}

void mergerSort(int arr[], int l, int r) {
    // TODO: implement recursive merge sort
}

} // namespace MergeSort

// ==================== TEST CASES ====================

TEST(MergeSort_BasicArray) {
    int arr[] = {5, 2, 8, 1, 9};
    MergeSort::mergerSort(arr, 0, 4);
    int expected[] = {1, 2, 5, 8, 9};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(MergeSort_AlreadySorted) {
    int arr[] = {1, 2, 3, 4, 5};
    MergeSort::mergerSort(arr, 0, 4);
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(MergeSort_ReverseSorted) {
    int arr[] = {5, 4, 3, 2, 1};
    MergeSort::mergerSort(arr, 0, 4);
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(MergeSort_SingleElement) {
    int arr[] = {42};
    MergeSort::mergerSort(arr, 0, 0);
    TestBase::assertEqual(42, arr[0]);
}

TEST(MergeSort_TwoElements) {
    int arr[] = {7, 3};
    MergeSort::mergerSort(arr, 0, 1);
    TestBase::assertEqual(3, arr[0]);
    TestBase::assertEqual(7, arr[1]);
}

TEST(MergeSort_TwoElementsSorted) {
    int arr[] = {3, 7};
    MergeSort::mergerSort(arr, 0, 1);
    TestBase::assertEqual(3, arr[0]);
    TestBase::assertEqual(7, arr[1]);
}

TEST(MergeSort_WithDuplicates) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    MergeSort::mergerSort(arr, 0, 9);
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    for (int i = 0; i < 10; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(MergeSort_AllSameElements) {
    int arr[] = {5, 5, 5, 5, 5};
    MergeSort::mergerSort(arr, 0, 4);
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(5, arr[i]);
    }
}

TEST(MergeSort_NegativeNumbers) {
    int arr[] = {-3, -1, -4, -1, -5};
    MergeSort::mergerSort(arr, 0, 4);
    int expected[] = {-5, -4, -3, -1, -1};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(MergeSort_MixedPositiveNegative) {
    int arr[] = {-2, 5, -8, 3, 0, -1, 7};
    MergeSort::mergerSort(arr, 0, 6);
    int expected[] = {-8, -2, -1, 0, 3, 5, 7};
    for (int i = 0; i < 7; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(MergeSort_LargeArray) {
    auto vec = TestBase::randomInts(100);
    int arr[100];
    for (int i = 0; i < 100; i++) arr[i] = vec[i];

    MergeSort::mergerSort(arr, 0, 99);

    for (int i = 0; i < 99; i++) {
        TestBase::assertTrue(arr[i] <= arr[i + 1], "Array should be sorted");
    }
}

TEST(MergeSort_PartialSort) {
    int arr[] = {9, 7, 5, 3, 1, 8, 6, 4, 2, 0};
    MergeSort::mergerSort(arr, 2, 6);
    int expected[] = {9, 7, 1, 3, 5, 6, 8, 4, 2, 0};
    for (int i = 0; i < 10; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}
