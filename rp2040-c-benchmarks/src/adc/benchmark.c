/**
 * @file benchmark.c
 * @brief ADC Read Timing Benchmark for RP2040.
 *
 * This benchmark measures the latency of single analog-to-digital conversions
 * using a potentiometer connected to GPIO26 (ADC0). Results are printed in CSV format
 * for analysis.
 *
 * Wiring:
 *   - GPIO26 (pin 31) → Wiper (middle pin) of potentiometer
 *   - 3.3V            → One side of potentiometer
 *   - GND             → Other side of potentiometer
 *
 * Output format:
 *   task,method,reads,avg_time_us
 *
 * Occasional read samples are also printed for verification purposes.
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/time.h"
#include "benchmarks.h"

/**
 * @brief Executes ADC benchmark by sampling from GPIO26 (ADC0).
 *
 * Performs 1000 single-sample ADC reads, times each operation individually,
 * and calculates the average latency per read. A subset of values is printed
 * for manual inspection.
 *
 * @note Output is CSV-formatted.
 * @return void
 */
void benchmark_adc(void) {
    const int NUM_READS = 1000;

    // Initialise ADC subsystem and GPIO26
    adc_init();
    adc_gpio_init(26);     // GP26 = ADC0
    adc_select_input(0);   // Select ADC0 as input

    printf("task,method,reads,avg_time_us\n");

    int64_t total_time = 0;

    for (int i = 0; i < NUM_READS; ++i) {
        absolute_time_t start = get_absolute_time();
        uint16_t value = adc_read();  // 12-bit result: 0–4095
        int64_t elapsed = absolute_time_diff_us(start, get_absolute_time());
        total_time += elapsed;

        // Print selected samples for debugging/visual validation
        if (i % 250 == 0) {
            printf("adc,sample,%d,%d\n", i, value);
        }
    }

    int64_t avg_time = total_time / NUM_READS;
    printf("adc,single_read,%d,%lld\n", NUM_READS, avg_time);
}
