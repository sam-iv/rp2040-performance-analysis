/**
 * @file benchmark.c
 * @brief Fibonacci Benchmark for RP2040 (Recursive vs Iterative).
 *
 * This benchmark measures and compares the execution time of two
 * Fibonacci implementations: recursive and iterative. The test is
 * designed to highlight differences in control flow and call overhead.
 *
 * Source (theoretical reference):
 * https://en.wikipedia.org/wiki/Fibonacci_number
 *
 * Output format:
 *   task,method,n,result,time_us
 *
 * Timing uses the Pico SDK and results are printed via USB serial in CSV format.
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "benchmarks.h"

/**
 * @brief Recursive Fibonacci implementation.
 *
 * Calculates the nth Fibonacci number using a basic recursive method.
 * This version is highly inefficient for large n due to repeated calls.
 *
 * @param n The index of the Fibonacci sequence (0-based).
 * @return The nth Fibonacci number.
 */
static int fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

/**
 * @brief Iterative Fibonacci implementation.
 *
 * Efficient calculation of the nth Fibonacci number using iteration.
 * Avoids call stack usage, making it suitable for embedded timing.
 *
 * @param n The index of the Fibonacci sequence (0-based).
 * @return The nth Fibonacci number.
 */
static int fib_iterative(int n) {
    if (n <= 1)
        return n;
    int prev = 0, curr = 1;
    for (int i = 2; i <= n; ++i) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

/**
 * @brief Run Fibonacci benchmarks on multiple input sizes.
 *
 * Times both iterative and recursive implementations for input values
 * 10, 20, 30, and 35. Results include calculated values and execution
 * time in microseconds.
 *
 * @note CSV format: task,method,n,result,time_us
 */
void benchmark_fibonacci(void) {
    const int test_values[] = {10, 20, 30, 35};
    int result;
    absolute_time_t start, end;
    int64_t elapsed_us;

    printf("task,method,n,result,time_us\n");

    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i) {
        int n = test_values[i];

        // Iterative variant
        start = get_absolute_time();
        result = fib_iterative(n);
        end = get_absolute_time();
        elapsed_us = absolute_time_diff_us(start, end);
        printf("fibonacci,iterative,%d,%d,%lld\n", n, result, elapsed_us);

        // Recursive variant
        start = get_absolute_time();
        result = fib_recursive(n);
        end = get_absolute_time();
        elapsed_us = absolute_time_diff_us(start, end);
        printf("fibonacci,recursive,%d,%d,%lld\n", n, result, elapsed_us);
    }
}
