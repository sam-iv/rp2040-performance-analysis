/**
 * @file benchmark.c
 * @brief FFT Benchmark for RP2040 (Radix-2, Cooley–Tukey algorithm).
 *
 * This benchmark evaluates the execution time of a radix-2 Fast Fourier Transform
 * using the Cooley–Tukey algorithm. It operates on a 128-point sine wave and
 * prints the execution duration in CSV format for analysis.
 *
 * Source (algorithmic reference):
 * https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
 *
 * Output format:
 *   task,method,size,time_us
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "benchmarks.h"

#define PI 3.14159265358979323846f

/**
 * @brief Rearrange input arrays into bit-reversed order.
 *
 * This step is required prior to performing a radix-2 Cooley-Tukey FFT.
 * Operates in-place on both the real and imaginary parts of the signal.
 *
 * @param real Pointer to the real input array.
 * @param imag Pointer to the imaginary input array.
 * @param n    Length of the arrays (must be a power of 2).
 */
static void bit_reverse(float* real, float* imag, int n) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i < j) {
            float temp = real[i];
            real[i] = real[j];
            real[j] = temp;

            temp = imag[i];
            imag[i] = imag[j];
            imag[j] = temp;
        }
        int m = n >> 1;
        while (j >= m && m > 0) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
}

/**
 * @brief Perform an in-place radix-2 Cooley-Tukey FFT.
 *
 * Computes the discrete Fourier transform of a complex input array
 * using a classic radix-2 butterfly algorithm. Input must already be
 * bit-reversed.
 *
 * @param real Pointer to the real component of the signal.
 * @param imag Pointer to the imaginary component of the signal.
 * @param n    Number of points (must be a power of 2).
 */
static void fft_radix2(float* real, float* imag, int n) {
    bit_reverse(real, imag, n);

    for (int s = 1; s <= log2f(n); s++) {
        int m = 1 << s;
        float angle = -2.0f * PI / m;
        float w_m_real = cosf(angle);
        float w_m_imag = sinf(angle);

        for (int k = 0; k < n; k += m) {
            float w_real = 1.0f;
            float w_imag = 0.0f;

            for (int j = 0; j < m / 2; j++) {
                int t = k + j;
                int u = t + m / 2;

                float t_real = w_real * real[u] - w_imag * imag[u];
                float t_imag = w_real * imag[u] + w_imag * real[u];

                real[u] = real[t] - t_real;
                imag[u] = imag[t] - t_imag;
                real[t] += t_real;
                imag[t] += t_imag;

                float w_tmp = w_real;
                w_real = w_real * w_m_real - w_imag * w_m_imag;
                w_imag = w_tmp * w_m_imag + w_imag * w_m_real;
            }
        }
    }
}

/**
 * @brief Run FFT benchmark on a 128-point sine wave.
 *
 * Generates a synthetic sine wave, computes its FFT using the
 * Cooley-Tukey radix-2 algorithm, and prints execution time.
 * Results are logged in CSV format.
 *
 * @note This benchmark uses a fixed size of 128 samples for consistency
 *       across language comparisons.
 */
void benchmark_fft(void) {
    const int N = 128;
    float real[N];
    float imag[N];

    // Generate synthetic sine wave input (real) with 0-valued imaginary parts
    for (int i = 0; i < N; i++) {
        real[i] = sinf(2 * PI * i / N);
        imag[i] = 0.0f;
    }

    // Time the FFT computation
    absolute_time_t start = get_absolute_time();
    fft_radix2(real, imag, N);
    int64_t elapsed = absolute_time_diff_us(start, get_absolute_time());

    // Output results in CSV format
    printf("task,method,size,time_us\n");
    printf("fft,radix2,%d,%lld\n", N, elapsed);
}
