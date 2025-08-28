/**
 * @file tools.c
 * @brief Entry point for RP2040 utility tools used in benchmarking support.
 *
 * This program runs support firmware on a secondary Pico (RP2040),
 * acting as a probe, logger, or responder to assist main benchmark tests.
 *
 * The active tool is selected by modifying the TOOL_MODE value below.
 *
 * Tool Mode Mapping:
 *   1 → GPIO Probe (edge logger on GPIO2)
 *   2 → UART Logger (listens on GPIO1)
 *   3 → I2C Passive Responder (SDA=GPIO8, SCL=GPIO9)
 *
 * Output is printed over USB serial. Each tool confirms its mode via banner output.
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "tool_functions.h"

#define TOOL_MODE 3  ///< Set to 1, 2, or 3 to select tool

int main() {
    stdio_init_all();
    sleep_ms(10000);  // Allow USB serial monitor to connect

    printf("Tool Mode: %d\n", TOOL_MODE);
    printf("----------------------\n");

    switch (TOOL_MODE) {
        case 1:
            run_gpio_probe();      // Monitor GPIO2 for rising/falling edges
            break;
        case 2:
            run_uart_logger();     // Listen on GPIO1 for UART input
            break;
        case 3:
            run_i2c_responder();   // Passive slave (responds to I2C master)
            break;
        default:
            printf("Invalid TOOL_MODE selected.\n");
            break;
    }

    while (1) {
        sleep_ms(5000);  // Keep USB serial open indefinitely
    }
}
