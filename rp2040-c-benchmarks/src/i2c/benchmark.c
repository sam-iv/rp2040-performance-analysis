/**
 * @file benchmark.c
 * @brief I2C Write Benchmark for RP2040 (Master to Slave).
 *
 * This benchmark measures the average time taken to send a 4-byte message
 * over I2C using the RP2040's hardware I2C0 peripheral. The test writes
 * repeatedly to a second Pico acting as a passive I2C responder.
 *
 * Wiring:
 *   - GPIO8 (pin 11) → SDA → GPIO8 on second Pico
 *   - GPIO9 (pin 12) → SCL → GPIO9 on second Pico
 *   - GND shared between devices
 *
 * The I2C master operates at 100 kHz and sends 100 messages to address 0x42.
 * Results are printed in CSV format via USB serial.
 *
 * Output format:
 *   task,method,iterations,total_time_us,avg_time_us
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

#define I2C_PORT i2c0
#define SDA_PIN 8
#define SCL_PIN 9
#define I2C_ADDR 0x42

/**
 * @brief Run I2C write benchmark to a known slave device.
 *
 * Sends 100 4-byte messages to an I2C slave at address 0x42 using I2C0.
 * Measures the total time taken and calculates average time per write.
 *
 * SDA: GPIO8
 * SCL: GPIO9
 *
 * @return void
 */
void benchmark_i2c(void) {
    stdio_init_all();
    sleep_ms(3000);  // Allow USB serial connection

    // Configure I2C0 for 100 kHz
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    const uint8_t message[4] = {'T', 'e', 's', 't'};
    const int loops = 100;

    printf("Benchmark: I2C Write\n");
    printf("task,method,iterations,total_time_us,avg_time_us\n");

    uint32_t start = time_us_32();

    for (int i = 0; i < loops; i++) {
        i2c_write_blocking(I2C_PORT, I2C_ADDR, message, 4, false);
    }

    uint32_t end = time_us_32();
    uint32_t duration = end - start;
    float avg = (float)duration / loops;

    // Print CSV-formatted results
    printf("i2c,write,%d,%lu,%.2f\n", loops, duration, avg);

    while (true) {
        sleep_ms(1000);  // Keep USB serial alive
    }
}
