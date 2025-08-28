/**
 * @file c_benchmarks.c
 * @brief Main entry point for benchmark execution on RP2040 (Raspberry Pi Pico).
 *
 * Selects and runs a specific benchmark based on the configured BENCHMARK_MODE.
 * This file acts as the top-level controller for both software and hardware tests.
 *
 * Mode mapping:
 *   1 → Software benchmark suite (Fibonacci, Sorting, FFT, etc.)
 *   2 → GPIO toggle timing
 *   3 → PWM setup timing
 *   4 → ADC read timing
 *   5 → Interrupt latency (button press → ISR)
 *   6 → UART transmission
 *   7 → I2C master write
 *
 * Note:
 *   USB serial output requires a delay before printing to ensure the host is ready.
 *   All benchmarks output results in CSV format.
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "benchmarks.h"

#define BENCHMARK_MODE 1  ///< Change this value to select which benchmark to run

int main() {
    stdio_init_all();
    sleep_ms(10000);  // Give USB serial host time to initialise

    printf("Benchmark Mode: %d\n", BENCHMARK_MODE);
    printf("----------------------\n");

    switch (BENCHMARK_MODE) {
        case 1:
            run_software_benchmarks();
            break;
        case 2:
            benchmark_gpio_toggle();     // GPIO output toggling test
            break;
        case 3:
            benchmark_pwm();             // PWM setup time measurement
            break;
        case 4:
            benchmark_adc();             // Analogue-to-digital read timing
            break;
        case 5:
            benchmark_interrupt();       // ISR latency from GPIO input
            break;
        case 6:
            benchmark_uart();            // UART TX timing (to logger Pico)
            break;
        case 7:
            benchmark_i2c();             // I2C master write latency
            break;
        default:
            printf("Invalid benchmark mode selected.\n");
            break;
    }

    // Keep USB serial active after benchmark completes
    while (true) {
        sleep_ms(5000);
    }
}
