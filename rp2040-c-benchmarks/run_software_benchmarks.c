/**
 * @file run_software_benchmarks.c
 * @brief Entry point for software-only benchmarks on RP2040.
 *
 * This file provides a single function to sequentially execute all
 * software-based benchmarks that do not rely on external circuitry.
 * Each benchmark outputs results in CSV format and is separated by
 * a visual divider for clarity when reading from the USB serial output.
 *
 * Benchmarks included:
 *   - Fibonacci (iterative & recursive)
 *   - Bubble Sort
 *   - Quick Sort
 *   - Loop Overhead
 *   - Matrix Multiplication
 *   - FFT (Radix-2)
 *
 * This function is used when BENCHMARK_MODE = 1 in the main application file.
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "benchmarks.h"

/**
 * @brief Run all software (non-hardware) benchmarks sequentially.
 *
 * Invokes each benchmark in order, printing a divider after each to improve
 * serial output readability. Benchmarks operate independently and do not
 * rely on any GPIO or hardware peripherals.
 *
 * @return void
 */
void run_software_benchmarks(void) {
    benchmark_fibonacci();
    printf("----------------------\n");

    benchmark_bubble_sort();
    printf("----------------------\n");

    benchmark_quick_sort();
    printf("----------------------\n");

    benchmark_loop_overhead();
    printf("----------------------\n");

    benchmark_matrix_multiplication();
    printf("----------------------\n");

    benchmark_fft();
    printf("----------------------\n");
}
