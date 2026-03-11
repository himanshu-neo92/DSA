// Problem: Quick Sort
// Implement the quick sort algorithm to sort an array in ascending order.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) average, O(n²) worst case
// Space Complexity: O(log n) - Recursion stack depth
//
// Key concepts:
// - Partition: choose a pivot, rearrange so elements < pivot are left, > pivot are right
// - Recursively sort left and right partitions
// - In-place sorting (no extra arrays needed)
// - Not stable (relative order of equal elements may change)
//
// Pivot selection strategies:
// - Last element (used here): simple but O(n²) on sorted input
// - Random: expected O(n log n)
// - Median-of-three: good practical performance
// =======================================================

#include "TestBase.h"

namespace QuickSort {

// ========== Solution ==========
void swap(int arr[], int i, int j) {
    // TODO: implement swap
}

int partiton(int arr[], int low, int high) {
    // TODO: implement partition (Lomuto scheme)
    // Choose arr[high] as pivot
    // Return final position of pivot
    return low;
}

void quickSort(int arr[], int low, int high) {
    // TODO: implement recursive quick sort
}

} // namespace QuickSort

// ==================== TEST CASES ====================

TEST(QuickSort_BasicArray) {
    int arr[] = {5, 2, 8, 1, 9};
    QuickSort::quickSort(arr, 0, 4);
    int expected[] = {1, 2, 5, 8, 9};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(QuickSort_AlreadySorted) {
    int arr[] = {1, 2, 3, 4, 5};
    QuickSort::quickSort(arr, 0, 4);
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(QuickSort_ReverseSorted) {
    int arr[] = {5, 4, 3, 2, 1};
    QuickSort::quickSort(arr, 0, 4);
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(QuickSort_SingleElement) {
    int arr[] = {42};
    QuickSort::quickSort(arr, 0, 0);
    TestBase::assertEqual(42, arr[0]);
}

TEST(QuickSort_TwoElements) {
    int arr[] = {7, 3};
    QuickSort::quickSort(arr, 0, 1);
    TestBase::assertEqual(3, arr[0]);
    TestBase::assertEqual(7, arr[1]);
}

TEST(QuickSort_TwoElementsSorted) {
    int arr[] = {3, 7};
    QuickSort::quickSort(arr, 0, 1);
    TestBase::assertEqual(3, arr[0]);
    TestBase::assertEqual(7, arr[1]);
}

TEST(QuickSort_WithDuplicates) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    QuickSort::quickSort(arr, 0, 9);
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    for (int i = 0; i < 10; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(QuickSort_AllSameElements) {
    int arr[] = {5, 5, 5, 5, 5};
    QuickSort::quickSort(arr, 0, 4);
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(5, arr[i]);
    }
}

TEST(QuickSort_NegativeNumbers) {
    int arr[] = {-3, -1, -4, -1, -5};
    QuickSort::quickSort(arr, 0, 4);
    int expected[] = {-5, -4, -3, -1, -1};
    for (int i = 0; i < 5; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(QuickSort_MixedPositiveNegative) {
    int arr[] = {-2, 5, -8, 3, 0, -1, 7};
    QuickSort::quickSort(arr, 0, 6);
    int expected[] = {-8, -2, -1, 0, 3, 5, 7};
    for (int i = 0; i < 7; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}

TEST(QuickSort_LargeArray) {
    auto vec = TestBase::randomInts(100);
    int arr[100];
    for (int i = 0; i < 100; i++) arr[i] = vec[i];

    QuickSort::quickSort(arr, 0, 99);

    for (int i = 0; i < 99; i++) {
        TestBase::assertTrue(arr[i] <= arr[i + 1], "Array should be sorted");
    }
}

TEST(QuickSort_PartialSort) {
    int arr[] = {9, 7, 5, 3, 1, 8, 6, 4, 2, 0};
    QuickSort::quickSort(arr, 2, 6);
    int expected[] = {9, 7, 1, 3, 5, 6, 8, 4, 2, 0};
    for (int i = 0; i < 10; i++) {
        TestBase::assertEqual(expected[i], arr[i]);
    }
}
