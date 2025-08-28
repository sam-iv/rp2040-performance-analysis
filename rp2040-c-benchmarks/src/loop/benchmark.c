/**
 * @file benchmark.c
 * @brief Loop Control Overhead Benchmark for RP2040.
 *
 * This benchmark measures the execution time of basic `for` loops
 * with increasing iteration counts. It is designed to evaluate
 * loop control overhead in a bare-metal environment using the RP2040.
 *
 * A `volatile` counter is used to prevent the compiler from optimising
 * the loop body away, ensuring accurate timing measurements.
 *
 * Output format:
 *   task,method,iterations,time_us
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "benchmarks.h"

/**
 * @brief Increment a volatile counter N times.
 *
 * Performs a simple loop-based increment operation. The counter is marked
 * as `volatile` to ensure the compiler does not remove or optimise away
 * the loop during compilation.
 *
 * @param sink Pointer to a volatile integer variable.
 * @param iterations Number of loop iterations to perform.
 */
static void loop_counter(volatile int* sink, int iterations) {
    for (int i = 0; i < iterations; i++) {
        *sink += 1;
    }
}

/**
 * @brief Run loop overhead benchmark with various iteration sizes.
 *
 * Tests increment loop overhead using four common scales: 1k, 10k, 100k, and 1M.
 * Outputs results in CSV format for external analysis or plotting.
 *
 * CSV format:
 *   task,method,iterations,time_us
 *
 * @return void
 */
void benchmark_loop_overhead(void) {
    int iterations[] = {1000, 10000, 100000, 1000000};
    volatile int sink = 0;

    printf("task,method,iterations,time_us\n");

    for (int i = 0; i < sizeof(iterations) / sizeof(int); i++) {
        int n = iterations[i];

        absolute_time_t start = get_absolute_time();
        loop_counter(&sink, n);
        int64_t elapsed = absolute_time_diff_us(start, get_absolute_time());

        printf("loop,for_loop,%d,%lld\n", n, elapsed);
    }
}
