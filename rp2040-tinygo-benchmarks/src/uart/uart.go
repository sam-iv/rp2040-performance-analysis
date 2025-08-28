package main

import (
	"machine"
	"time"
)

// benchmarkUART measures the time required to send a string
// over the RP2040’s UART0 peripheral. It uses GPIO0 as the TX pin
// and assumes either a second Pico is connected for logging, or a loopback test.
//
// Wiring:
//   - GPIO0 (pin 1) → GPIO1 (RX) on second Pico logger
//   - GND shared between both boards
//
// Each character is transmitted using uart.WriteByte() to reflect actual byte-wise performance.
//
// Output format:
//   task,method,iterations,total_time_us,avg_time_us
func benchmarkUART() {
	// UART benchmark parameters
	const iterations = 100
	const baud = 115200
	const txPin = machine.GPIO0
	message := []byte("Hello from main Pico\n")

	// Configure the UART peripheral
	uart := machine.UART0
	uart.Configure(machine.UARTConfig{
		TX:       txPin,
		BaudRate: baud,
	})

	println("Benchmark: UART Send")
	println("task,method,iterations,total_time_us,avg_time_us")

	start := time.Now()

	// Send the message multiple times
	for i := 0; i < iterations; i++ {
		for _, b := range message {
			uart.WriteByte(b)
		}
	}

	// Calculate the total time taken and average time per iteration
	duration := time.Since(start).Microseconds()
	avg := float64(duration) / float64(iterations)

	println("uart,send,", iterations, ",", duration, ",", avg)
}
