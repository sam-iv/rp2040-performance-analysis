/**
 * @file benchmark.c
 * @brief GPIO Toggle Benchmark for RP2040.
 *
 * This benchmark measures the time required to toggle a digital output pin
 * repeatedly. It evaluates the performance of GPIO write operations on the RP2040.
 *
 * Output is provided in CSV format for automated analysis. Optional slow toggling
 * can be enabled to allow visible/audible confirmation via buzzer and logger probe.
 *
 * Wiring:
 *   - GPIO2 (Pin 4) → Buzzer anode (long leg)
 *   - GPIO2 (Pin 4) → Logger probe (if possible)
 *   - Buzzer cathode → GND
 *   - Common ground shared between both boards
 *
 * Note:
 * The RP2040 toggles GPIO faster than a buzzer or second Pico can reliably detect.
 * If `SLOW_TOGGLE` is defined, short delays are added to make activity visible
 * and audible for external confirmation. These delays should be disabled
 * for accurate benchmarking and shouldn't impact the results as SLOW_TOGGLE
 * is not defined in the final build.
 *
 * Output format:
 *   toggles,total_time_us,avg_toggle_us
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#define TOGGLE_PIN 2
#define TOGGLE_COUNT 1000

// Uncomment for probe/buzzer verification
//#define SLOW_TOGGLE

void benchmark_gpio_toggle(void) {
    gpio_init(TOGGLE_PIN);
    gpio_set_dir(TOGGLE_PIN, GPIO_OUT);

    // Allow USB serial connection to initialise
    sleep_ms(3000);

    printf("Benchmark: GPIO Toggle\n");
    printf("toggles,total_time_us,avg_toggle_us\n");

    uint32_t start = time_us_32();

    for (int i = 0; i < TOGGLE_COUNT; i++) {
        gpio_put(TOGGLE_PIN, 1);
    #ifdef SLOW_TOGGLE
        sleep_us(100);  // ~5kHz audible tone
    #endif
        gpio_put(TOGGLE_PIN, 0);
    #ifdef SLOW_TOGGLE
        sleep_us(100);
    #endif
    }

    uint32_t end = time_us_32();
    uint32_t duration = end - start;
    float avg = (float)duration / TOGGLE_COUNT;

    // Output benchmark results
    printf("%d,%lu,%.2f\n", TOGGLE_COUNT, duration, avg);

    // Keep the USB serial active after benchmarking
    while (true) {
        sleep_ms(1000);
    }
}
