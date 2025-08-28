/**
 * @file probe.c
 * @brief GPIO Edge Logger Tool for RP2040 (Tool Mode 1)
 *
 * Continuously monitors a digital input pin (GPIO2) and logs transitions
 * (rising and falling edges) with microsecond timestamps via USB serial.
 *
 * Used in conjunction with GPIO/PWM benchmarks to verify timing
 * or detect logic activity.
 *
 * Output format:
 *   timestamp_us,state
 *
 * Wiring:
 *   - GPIO2 (Logger) ← GPIO2 (Main Pico output)
 *   - GND (Logger)   ← GND (Main Pico)
 *
 * Notes:
 *   - Both Picos must share a common ground reference.
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include <stdio.h>

#define PROBE_PIN 2        // GPIO to monitor for logic changes
#define DEBOUNCE_US 1      // Optional debounce/pacing (in microseconds)

/**
 * @brief Run GPIO edge logger.
 *
 * Continuously samples the input pin and prints a timestamped CSV line
 * whenever a logic level change (edge) is detected. Suitable for logging
 * PWM or rapid toggling activity.
 *
 * @return void
 */
void run_gpio_probe(void) {
    gpio_init(PROBE_PIN);
    gpio_set_dir(PROBE_PIN, GPIO_IN);

    printf("timestamp_us,state\n");

    uint8_t last = gpio_get(PROBE_PIN);

    while (true) {
        uint8_t current = gpio_get(PROBE_PIN);
        if (current != last) {
            uint32_t timestamp = time_us_32();
            printf("%lu,%d\n", timestamp, current);
            last = current;
        }

        sleep_us(DEBOUNCE_US);  // Sampling interval / pacing
    }
}
