// Problem: Merge Sort
// Sort an array using the divide-and-conquer merge sort algorithm
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) - Divides array in half each level, merges in O(n) per level
// Space Complexity: O(n) - Temporary arrays used during merge step
//
// Alternative approaches:
// - Quick Sort: O(n log n) avg time, O(log n) space - In-place but unstable, O(n²) worst case
// - Heap Sort: O(n log n) time, O(1) space - In-place but not stable, poor cache locality
// - Tim Sort: O(n log n) time, O(n) space - Hybrid approach, exploits existing order
//
// Why this approach is optimal:
// - Guaranteed O(n log n) worst-case time unlike Quick Sort
// - Stable sort preserves relative order of equal elements
// - Divide and conquer provides natural parallelism
// =======================================================

#include "TestBase.h"

namespace MergeSort {

    void mergeArray(int arr[], int l, int m, int r) {

        // size of left array is l to mid
        const int leftSize = m - l + 1;
        // size of right is mid to right
        const int rightSize = r - m;
        int leftArr[leftSize];
        int rightArr[ rightSize];
        int i =0;

        // Copy over the elements
        for (int i =0; i<leftSize; ++i){
            leftArr[i] = arr[l + i];
        }

        for (i =0; i<rightSize; ++i ) {
            rightArr[i] = arr[m + 1 + i];
        }


        // select the elemets from the partitions
        i =0;
        int j = 0, k =l;
        while (i < leftSize && j < rightSize) {
            if ( leftArr[i] < rightArr[j]) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }

        // fill the rest of the elements
        while ( i < leftSize) {
                arr[k++] = leftArr[i++];
        }

        while ( j < rightSize) {
            arr[k++] = rightArr[j++];
        }

    }

    void mergerSort(int arr[], int l , int r) {

        if ( l < r) {
            int m = (l + r) / 2;
            mergerSort(arr, l, m);
            mergerSort(arr, m +1, r);
            mergeArray(arr, l, m , r);
        }
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
