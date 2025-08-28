package main

import (
	"machine"
	"time"
)

// benchmarkBubbleSort runs the Bubble Sort benchmark on various array sizes.
//
// This function benchmarks the Bubble Sort algorithm by filling a slice
// with descending values (worst-case scenario) and measuring the time taken
// to sort it. The results are printed in CSV format via USB serial.
//
// Test sizes: 10, 50, and 100.
// Output format: task,method,size,time_us
func benchmarkBubbleSort() {
	sizes := []int{10, 50, 100}
	println("task,method,size,time_us")

	for _, size := range sizes {
		// Create reverse-ordered array (worst-case input for bubble sort)
		data := make([]int, size)
		for i := 0; i < size; i++ {
			data[i] = size - i
		}

		start := time.Now()
		BubbleSort(data)
		elapsed := time.Since(start).Microseconds()

		println("bubblesort,bubble,", size, ",", elapsed)
	}
}

// main initializes USB serial and starts the benchmark runner.
//
// Waits 10 seconds to ensure the USB serial monitor connects properly before output.
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(time.Second * 10) // allow serial connection to stabilize

	println("TinyGo Bubble Sort Benchmark Starting...")
	benchmarkBubbleSort()

	// Prevent exit (TinyGo needs main to block or loop forever)
	for {
		time.Sleep(time.Second * 10)
	}
}
