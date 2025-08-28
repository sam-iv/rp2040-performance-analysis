/**
 * @file benchmark.c
 * @brief PWM Setup Time Benchmark for RP2040.
 *
 * This benchmark measures the time taken to configure and start
 * a PWM signal on a designated GPIO pin using the RP2040's hardware PWM peripheral.
 *
 * Wiring:
 *   - GPIO15 (pin 20) → Positive terminal of buzzer and/or probe input
 *   - Buzzer GND → Common GND rail
 *
 * It does not measure waveform timing accuracy, but rather the latency of setup
 * and activation. The signal can be verified using a buzzer or a second Pico logic probe.
 *
 * Output format:
 *   task,method,setup_time_us
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define PWM_GPIO 15  // GPIO15 = physical pin 20

/**
 * @brief Run PWM setup benchmark on GPIO15.
 *
 * Configures a PWM signal with a 50% duty cycle on GPIO15.
 * Measures the time from start of configuration to signal activation.
 * Outputs results in CSV format.
 *
 * @return void
 */
void benchmark_pwm(void) {
    gpio_set_function(PWM_GPIO, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO);

    sleep_ms(3000);  // Allow USB serial monitor to connect

    printf("Benchmark: PWM Setup\n");
    printf("task,method,setup_time_us\n");

    uint32_t start = time_us_32();

    // Configure PWM peripheral
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f);      // Optional: reduce frequency
    pwm_init(slice_num, &config, false);       // Initialisation (PWM disabled)

    pwm_set_gpio_level(PWM_GPIO, 128);         // 50% duty cycle (range: 0–255)
    pwm_set_enabled(slice_num, true);          // Activate PWM

    uint32_t end = time_us_32();
    uint32_t duration = end - start;

    // Output result
    printf("pwm,setup,%lu\n", duration);

    // Keep PWM running and serial active
    while (true) {
        sleep_ms(1000);
    }
}
