// Problem: Quick Sort
// Sort an array using the quick sort algorithm with Lomuto partition scheme
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n log n) average, O(n²) worst case - Worst case with sorted/nearly sorted input
// Space Complexity: O(log n) - Recursive call stack depth in average case
//
// Alternative approaches:
// - Hoare partition: Fewer swaps on average, pivot stays in middle
// - Randomized pivot: Avoids worst-case on sorted input
// - Three-way partition (Dutch National Flag): Better for arrays with many duplicates
// - Merge Sort: O(n log n) guaranteed but O(n) extra space
//
// Why this approach is optimal:
// - Lomuto partition is simpler to implement and reason about
// - In-place sorting with minimal extra memory (only call stack)
// - Excellent cache locality due to sequential memory access
// - Average case O(n log n) performs well in practice
// =======================================================

#include "TestBase.h"

namespace QuickSort {

  void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  int partiton(int arr[], int low, int high) {
    const int piviot = arr[high];
    int i = low - 1;
    int j = low;
    while (j < high) {
      if (arr[j] <= piviot) {
        swap(arr, ++i, j);
      }
      ++j;
    }

    swap(arr, ++i, high);
    return i;

  }

  void quickSort(int arr[], int low, int high) {
    if (low < high) {
      const int piviot = partiton(arr, low, high);
      quickSort(arr, low, piviot - 1);
      quickSort(arr, piviot + 1, high);
    }
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
