/**
 * @file benchmark.c
 * @brief UART Transmission Benchmark for RP2040 (TX-only).
 *
 * This benchmark measures the time required to send a string
 * over the RP2040’s UART0 peripheral. It uses GPIO0 as the TX pin
 * and assumes either a second Pico is connected for logging, or a loopback test.
 *
 * Wiring:
 *   - GPIO0 (pin 1) → GPIO1 (RX) on second Pico logger
 *   - GND shared between both boards
 *
 * Each character is transmitted using `uart_putc()` to reflect actual byte-wise performance.
 *
 * Output format:
 *   task,method,iterations,total_time_us,avg_time_us
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_ID uart0
#define UART_TX_PIN 0   // GPIO0 = physical pin 1
#define BAUD_RATE 115200

/**
 * @brief Run UART transmission benchmark.
 *
 * Sends a fixed string ("Hello from main Pico\\n") 100 times over UART0 TX.
 * Each character is sent individually to simulate real-world character output.
 * Total and average time per transmission are measured and printed in CSV format.
 *
 * TX: GPIO0, 115200 baud
 *
 * @return void
 */
void benchmark_uart(void) {
    stdio_init_all();
    sleep_ms(3000);  // Allow USB serial to connect

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);

    const char *msg = "Hello from main Pico\n";
    const int loops = 100;

    printf("Benchmark: UART Send\n");
    printf("task,method,iterations,total_time_us,avg_time_us\n");

    uint32_t start = time_us_32();

    for (int i = 0; i < loops; i++) {
        const char *ptr = msg;
        while (*ptr) {
            uart_putc(UART_ID, *ptr++);  // Send each character individually
        }
    }

    uint32_t end = time_us_32();
    uint32_t duration = end - start;
    float avg = (float)duration / loops;

    printf("uart,send,%d,%lu,%.2f\n", loops, duration, avg);

    // Keep USB serial active
    while (true) {
        sleep_ms(1000);
    }
}
