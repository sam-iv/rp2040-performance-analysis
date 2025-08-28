/**
 * @file benchmark.c
 * @brief GPIO Interrupt Latency Benchmark for RP2040.
 *
 * This benchmark measures the latency between a GPIO edge event (from a button press)
 * and the invocation of its interrupt service routine (ISR). A second GPIO is used
 * to activate a buzzer, confirming the interrupt visually and audibly.
 *
 * Wiring:
 *   - GPIO14 (pin 19) → One leg of button
 *   - Other button leg → 3.3v (pin 36)
 *   - GPIO14 (pin 19) → GND rail (pulled down)
 *   - GPIO15 (pin 20) → Positive terminal of buzzer (active high)
 *   - Buzzer GND → Common GND rail
 *
 * Output format:
 *   task,method,latency_us
 *
 * The button is connected to GPIO14 (input), and the buzzer is connected to GPIO15 (output).
 *
 * @author Samuel Ivuerah
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdbool.h>

#define BUTTON_GPIO 14      // GPIO14 = pin 19 (input from button)
#define BUZZER_GPIO 15      // GPIO15 = pin 20 (output to buzzer)

volatile uint32_t irq_start_time = 0;
volatile uint32_t irq_latency = 0;
volatile bool trigger_buzz = false;

/**
 * @brief GPIO interrupt callback function.
 *
 * This ISR is triggered on both rising and falling edges on BUTTON_GPIO.
 * It records the interrupt latency, prints the result, and activates
 * the buzzer in the main loop.
 *
 * @param gpio The GPIO pin that triggered the interrupt.
 * @param events The type of edge event (rise or fall).
 */
void gpio_irq_callback(uint gpio, uint32_t events) {
    printf("ISR triggered on GPIO %d! Event: %lu\n", gpio, events);

    irq_latency = time_us_32() - irq_start_time;
    printf("interrupt,triggered,%lu\n", irq_latency);

    trigger_buzz = true;
}

/**
 * @brief Run the interrupt latency benchmark using a button press.
 *
 * Waits for an external GPIO interrupt and measures the time between the
 * polling loop and ISR execution. Activates a buzzer for visual confirmation.
 * Outputs timing data in CSV format for each event.
 *
 * Wiring:
 *   - Button: GPIO14 (input, pulled down)
 *   - Buzzer: GPIO15 (output, active-high)
 *
 * @return void
 */
void benchmark_interrupt(void) {
    stdio_init_all();
    sleep_ms(3000);  // Give USB time to connect

    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_down(BUTTON_GPIO);

    gpio_init(BUZZER_GPIO);
    gpio_set_dir(BUZZER_GPIO, GPIO_OUT);
    gpio_put(BUZZER_GPIO, 0);

    gpio_set_irq_enabled_with_callback(
        BUTTON_GPIO,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        &gpio_irq_callback
    );

    printf("Benchmark: Interrupt Latency\n");
    printf("task,method,latency_us\n");
    printf("Press the button to trigger interrupt...\n");

    while (true) {
        // Capture timestamp before polling for event
        irq_start_time = time_us_32();

        // If ISR was triggered, activate buzzer briefly
        if (trigger_buzz) {
            gpio_put(BUZZER_GPIO, 1);
            sleep_ms(50);
            gpio_put(BUZZER_GPIO, 0);
            trigger_buzz = false;
        }

        tight_loop_contents();  // Hint to compiler that we're intentionally spinning
    }
}
