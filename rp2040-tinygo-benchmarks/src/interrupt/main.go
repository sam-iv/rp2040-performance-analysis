package main

import (
	"machine"
	"time"
)

// main is the entry point for the TinyGo benchmark.
//
// It initializes USB serial, prints a start message,
// and calls the benchmark function defined in this folder.
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(10 * time.Second)

	println("TinyGo Interrupt Benchmark Starting...")
	benchmarkInterrupt()

	for {
		time.Sleep(10 * time.Second)
	}
}
