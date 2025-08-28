/**
 * @file benchmark.c
 * @brief Benchmark of the Bubble Sort algorithm on the RP2040.
 *
 * This benchmark evaluates the performance of the Bubble Sort algorithm,
 * a comparison-based sorting technique that repeatedly swaps adjacent
 * elements to order an array.
 *
 * Arrays are reverse-ordered to simulate worst-case performance.
 * Results are printed in CSV format via USB serial.
 *
 * Source (algorithmic reference):
 * https://en.wikipedia.org/wiki/Bubble_sort
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
 * @brief In-place Bubble Sort implementation.
 *
 * Sorts an integer array using the classic Bubble Sort algorithm,
 * which repeatedly compares and swaps adjacent elements until the
 * array is fully ordered.
 *
 * @param arr Pointer to the array to be sorted.
 * @param n   Number of elements in the array.
 */
static void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Executes the Bubble Sort benchmark for various array sizes.
 *
 * Populates arrays in descending order to represent the worst-case input
 * for Bubble Sort. Measures the time taken to sort each array using the
 * Pico SDK’s high-resolution timer. Outputs are printed in CSV format.
 *
 * @note Tested sizes: 10, 50, 100
 * @note CSV format: task,method,size,time_us
 */
void benchmark_bubble_sort(void) {
    int sizes[] = {10, 50, 100};
    int test[100];  // Sorting buffer

    printf("task,method,size,time_us\n");

    for (int s = 0; s < sizeof(sizes) / sizeof(int); s++) {
        int n = sizes[s];

        // Populate array in descending order (worst-case input)
        for (int i = 0; i < n; i++) {
            test[i] = n - i;
        }

        // Time the sorting operation
        absolute_time_t start = get_absolute_time();
        bubble_sort(test, n);
        int64_t elapsed = absolute_time_diff_us(start, get_absolute_time());

        // Print result in CSV format
        printf("bubblesort,bubble,%d,%lld\n", n, elapsed);
    }
}
