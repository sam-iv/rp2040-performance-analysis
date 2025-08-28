/**
 * @file responder.c
 * @brief I2C Passive Responder Tool for RP2040 (Tool Mode 3)
 *
 * This utility configures the RP2040 as a passive I2C responder using I2C0
 * on GPIO8 (SDA) and GPIO9 (SCL). It does not implement full slave logic,
 * but will acknowledge incoming writes from a master for benchmarking purposes.
 *
 * Used in the C vs TinyGo benchmarking project to confirm I2C write throughput.
 *
 * Output:
 *   - Prints banner message when ready
 *   - Passive during communication (no reads/writes, just ACKs)
 *
 * Wiring:
 *   - GPIO8 (SDA) ↔ Main Pico GPIO8 (SDA)
 *   - GPIO9 (SCL) ↔ Main Pico GPIO9 (SCL)
 *   - GND         ↔ GND (shared)
 *
 * Notes:
 *   - This tool only acknowledges writes. It does not respond with data.
 *   - I2C Baudrate: 100 kHz
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

#define I2C_SLAVE i2c0
#define SDA_PIN 8
#define SCL_PIN 9

/**
 * @brief Initialise I2C0 and enter passive responder loop.
 *
 * Configures GPIO8/9 for I2C and runs indefinitely. This tool
 * enables a master Pico to benchmark I2C write latency by
 * acknowledging transmissions at address 0x42 or similar.
 *
 * @return void
 */
void run_i2c_responder(void) {
    stdio_init_all();
    sleep_ms(3000);  // Wait for USB serial to connect

    printf("I2C Passive Responder Ready (GPIO8/9, 100kHz)\n");

    // Initialise I2C0 with standard speed (100 kHz)
    i2c_init(I2C_SLAVE, 100 * 1000);

    // Configure I2C pins and enable internal pull-ups
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Passive loop – nothing to handle, just keep I2C alive
    while (true) {
        tight_loop_contents();  // Low-power idle
    }
}
