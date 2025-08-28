/**
 * @file benchmark.c
 * @brief Quick Sort Benchmark for RP2040 (Recursive, Lomuto Partition).
 *
 * This benchmark evaluates the execution time of the Quick Sort algorithm
 * using recursive calls and the Lomuto partition scheme. Arrays are populated
 * in descending order to simulate a worst-case scenario for sorting performance.
 *
 * The test compares execution time across different input sizes, printing the results
 * in CSV format via USB serial.
 *
 * Source (algorithmic reference):
 * https://en.wikipedia.org/wiki/Quicksort
 *
 * Output format:
 *   task,method,size,time_us
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "benchmarks.h"

/**
 * @brief Partition the array using the Lomuto partition scheme.
 *
 * Chooses the last element as the pivot. Reorders the array such that
 * all values less than the pivot come before it, and all greater values
 * follow it. Returns the final position of the pivot.
 *
 * @param arr  Pointer to the array.
 * @param low  Lower index bound.
 * @param high Upper index bound.
 * @return Index of the pivot after partitioning.
 */
static int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
}

/**
 * @brief Recursive Quick Sort implementation (in-place).
 *
 * Sorts an array using the divide-and-conquer approach. This implementation
 * uses the Lomuto partitioning method and is sensitive to input order.
 *
 * @param arr  Pointer to the array.
 * @param low  Start index.
 * @param high End index.
 */
static void quick_sort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

/**
 * @brief Run Quick Sort benchmark using descending inputs.
 *
 * Benchmarks Quick Sort execution time across three input sizes (10, 50, 100).
 * Each array is filled in reverse order to simulate a worst-case scenario.
 * Results are printed in CSV format.
 *
 * CSV format:
 *   task,method,size,time_us
 *
 * @return void
 */
void benchmark_quick_sort(void) {
    int sizes[] = {10, 50, 100};
    int test[100];

    printf("task,method,size,time_us\n");

    for (int s = 0; s < sizeof(sizes) / sizeof(int); s++) {
        int n = sizes[s];

        // Fill array in descending order (worst-case input)
        for (int i = 0; i < n; i++) {
            test[i] = n - i;
        }

        // Time the sort
        absolute_time_t start = get_absolute_time();
        quick_sort(test, 0, n - 1);
        int64_t elapsed = absolute_time_diff_us(start, get_absolute_time());

        // Output results in CSV
        printf("quicksort,quick,%d,%lld\n", n, elapsed);
    }
}
