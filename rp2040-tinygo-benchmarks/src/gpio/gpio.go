package main

import (
	"machine"
	"time"
)

// benchmarkGPIOToggle measures the time required to toggle a digital output pin
// repeatedly. It evaluates the performance of GPIO write operations on the RP2040.
//
// Output is provided in CSV format for automated analysis. No delays are included,
// ensuring accurate benchmarking results.
//
// Wiring:
//   - GPIO2 (Pin 4) → Logger probe (GPIO2 on second Pico)
//   - GPIO2 (Pin 4) → Buzzer anode (optional for audible confirmation)
//   - Buzzer cathode → GND
//   - Common ground shared between both boards
//
// Note:
// The RP2040 toggles GPIO faster than external devices (like buzzers or loggers)
// can reliably detect. No artificial delays are included in this build.
//
// Output format:
//   gpio,toggle,<count>,<total_time_us>,<avg_toggle_us>
func benchmarkGPIOToggle() {
	const pin = machine.GPIO2
	const toggleCount = 1000

	pin.Configure(machine.PinConfig{Mode: machine.PinOutput})

	// Allow USB serial connection to initialise
	time.Sleep(3 * time.Second)

	println("task,method,toggles,total_time_us,avg_us")

	start := time.Now()

	for i := 0; i < toggleCount; i++ {
		pin.High()
		pin.Low()
	}

	duration := time.Since(start).Microseconds()
	avg := float64(duration) / float64(toggleCount)

	println("gpio,toggle,", toggleCount, ",", duration, ",", avg)
}
