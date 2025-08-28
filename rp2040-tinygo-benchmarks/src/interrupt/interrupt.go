package main

import (
	"machine"
	"time"
)

const (
	buttonPin = machine.GPIO14 // GPIO14 = pin 19 (input from button)
	buzzerPin = machine.GPIO15 // GPIO15 = pin 20 (output to buzzer)
)

var (
	triggered  = false
	irqStart   int64
	irqLatency int64
)

/*
 * handleInterrupt is the GPIO interrupt callback function.
 *
 * This ISR is triggered on both rising and falling edges on GPIO14.
 * It records the interrupt latency, prints the result, and signals
 * the main loop to activate the buzzer.
 */
func handleInterrupt(pin machine.Pin) {
	irqLatency = time.Since(time.UnixMicro(irqStart)).Microseconds()
	println("interrupt,triggered,", irqLatency)
	triggered = true
}

/*
 * benchmarkInterrupt sets up a GPIO interrupt on GPIO14 and measures
 * the latency between polling and ISR execution.
 *
 * A button is connected to GPIO14 (input with pull-down), and a buzzer
 * is connected to GPIO15 (output, active-high) to provide visual and
 * audible feedback upon interrupt.
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
 */
func benchmarkInterrupt() {
	println("Benchmark: Interrupt Latency")
	println("task,method,latency_us")
	println("Press the button to trigger interrupt...")

	buttonPin.Configure(machine.PinConfig{Mode: machine.PinInputPulldown})
	buzzerPin.Configure(machine.PinConfig{Mode: machine.PinOutput})
	buzzerPin.Low()

	buttonPin.SetInterrupt(machine.PinToggle, handleInterrupt)

	for {
		// Capture timestamp before polling
		irqStart = time.Now().UnixMicro()

		// If ISR triggered, activate buzzer briefly
		if triggered {
			buzzerPin.High()
			time.Sleep(50 * time.Millisecond)
			buzzerPin.Low()
			triggered = false
		}

		time.Sleep(1 * time.Millisecond)
	}
}
