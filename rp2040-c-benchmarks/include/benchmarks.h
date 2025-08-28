/**
 * @file benchmarks.h
 * @brief Declarations for benchmark functions on the RP2040 (Raspberry Pi Pico).
 *
 * This header provides prototypes for all implemented benchmarks used in the
 * performance comparison between C and TinyGo. Benchmarks are grouped into
 * software-only CPU tasks and hardware interaction tests (e.g., GPIO, ADC, UART).
 *
 * Each benchmark is invoked from the main control file using a mode selector.
 *
 * @author Samuel Ivuerah
 */

#ifndef BENCHMARKS_H
#define BENCHMARKS_H

// -----------------------------------------------------------------------------
// Software Benchmarks (CPU-bound, no external components)
// -----------------------------------------------------------------------------

/**
 * @brief Run all implemented software benchmarks sequentially.
 */
void run_software_benchmarks(void);

/**
 * @brief Benchmark recursive and iterative Fibonacci calculations.
 */
void benchmark_fibonacci(void);

/**
 * @brief Benchmark Bubble Sort on reverse-ordered integer arrays.
 */
void benchmark_bubble_sort(void);

/**
 * @brief Benchmark Quick Sort using worst-case array input.
 */
void benchmark_quick_sort(void);

/**
 * @brief Benchmark overhead of a simple for-loop (increment test).
 */
void benchmark_loop_overhead(void);

/**
 * @brief Benchmark matrix multiplication using fixed 2D arrays.
 */
void benchmark_matrix_multiplication(void);

/**
 * @brief Benchmark 128-point radix-2 FFT on a sine wave signal.
 */
void benchmark_fft(void);

// -----------------------------------------------------------------------------
// Hardware Benchmarks (timing with GPIOs, peripherals)
// -----------------------------------------------------------------------------

/**
 * @brief Benchmark ADC read latency on GPIO26 (ADC0).
 */
void benchmark_adc(void);

/**
 * @brief Benchmark GPIO toggle timing using GPIO2 and logger probe.
 */
void benchmark_gpio_toggle(void);

/**
 * @brief Benchmark PWM configuration and activation on GPIO15.
 */
void benchmark_pwm(void);

/**
 * @brief Benchmark interrupt latency using button press on GPIO14.
 */
void benchmark_interrupt(void);

/**
 * @brief Benchmark UART transmission to second Pico logger.
 */
void benchmark_uart(void);

/**
 * @brief Benchmark I2C master write latency to second Pico responder.
 */
void benchmark_i2c(void);

#endif  // BENCHMARKS_H
