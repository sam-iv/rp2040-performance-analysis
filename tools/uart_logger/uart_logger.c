/**
 * @file uart_logger.c
 * @brief UART Logger Tool for RP2040 (Tool Mode 2)
 *
 * This utility configures the RP2040 as a UART receiver (RX only) and echoes
 * incoming serial characters received on GPIO1 to USB serial output. It allows
 * a second Pico to monitor UART transmissions from a primary benchmarking device.
 *
 * Used to verify UART TX behaviour in the C vs TinyGo benchmarking project.
 *
 * Output:
 *   - Received characters printed in real-time via USB
 *
 * Wiring:
 *   - GPIO1 (Logger RX) ← GPIO0 (Main Pico TX)
 *   - GND (Logger)      ← GND (Main Pico)
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_RX_PIN 1  // GPIO1 = physical pin 2

/**
 * @brief Starts the UART logger tool on GPIO1.
 *
 * Continuously listens for characters over UART at 115200 baud and echoes
 * them to the USB serial interface. Useful for validating UART benchmark output.
 *
 * @return void
 */
void run_uart_logger(void) {
    // Initialise UART0 at specified baud rate
    uart_init(UART_ID, BAUD_RATE);

    // Set GPIO1 as UART RX
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    printf("UART Logger Ready (RX on GPIO1)\n");

    // Main loop: Echo any received UART characters over USB
    while (true) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            putchar(c);  // Forward to USB
        }
    }
}
