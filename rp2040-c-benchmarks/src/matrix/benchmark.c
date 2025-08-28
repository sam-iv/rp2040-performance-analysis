/**
 * @file benchmark.c
 * @brief Matrix Multiplication Benchmark for RP2040.
 *
 * This benchmark evaluates the performance of a square matrix multiplication
 * algorithm using fixed-size 2D integer arrays. It multiplies two NxN matrices
 * for N = 10 and 20, and measures the time taken using the RP2040's internal timer.
 *
 * This test is designed to capture loop nesting depth and memory access patterns.
 * Results are printed in CSV format over USB serial.
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
 * @brief Multiply two square integer matrices (A × B = C).
 *
 * Standard matrix multiplication algorithm. Operates in-place on
 * 2D integer arrays using triple-nested loops. Max matrix size is
 * constrained to 20x20 for simplicity and static memory allocation.
 *
 * @param size Size of the matrix (NxN).
 * @param A Left-hand input matrix.
 * @param B Right-hand input matrix.
 * @param C Output matrix to store the result.
 */
static void matrix_multiply(int size, int A[][20], int B[][20], int C[][20]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/**
 * @brief Run matrix multiplication benchmark for 10×10 and 20×20 inputs.
 *
 * Initialises matrices A and B with predefined integer values. Measures the
 * execution time of multiplying A × B into output matrix C. Each test result
 * is printed in CSV format, showing matrix size and timing in microseconds.
 *
 * CSV format:
 *   task,method,size,time_us
 *
 * @return void
 */
void benchmark_matrix_multiplication(void) {
    int sizes[] = {10, 20};

    int A[20][20];
    int B[20][20];
    int C[20][20];

    printf("task,method,size,time_us\n");

    for (int s = 0; s < sizeof(sizes) / sizeof(int); s++) {
        int n = sizes[s];

        // Populate test matrices with sample data
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }

        // Time the matrix multiplication
        absolute_time_t start = get_absolute_time();
        matrix_multiply(n, A, B, C);
        int64_t elapsed = absolute_time_diff_us(start, get_absolute_time());

        // Print result in CSV format
        printf("matrix,multiply,%d,%lld\n", n, elapsed);
    }
}
