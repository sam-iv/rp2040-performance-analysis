package main

import (
	"machine"
	"time"
)

// benchmarkQuickSort runs a benchmark for the Quick Sort algorithm.
//
// This function benchmarks Quick Sort on reversed arrays of sizes 10, 50, and 100,
// simulating worst-case scenarios. The execution time is printed in CSV format.
//
// Output format:
//   task,method,size,time_us
func benchmarkQuickSort() {
	sizes := []int{10, 50, 100}
	println("task,method,size,time_us")

	for _, size := range sizes {
		// Reversed array = worst case
		data := make([]int, size)
		for i := 0; i < size; i++ {
			data[i] = size - i
		}

		start := time.Now()
		QuickSort(data, 0, size-1)
		elapsed := time.Since(start).Microseconds()

		println("quicksort,quick,", size, ",", elapsed)
	}
}

// main is the entry point for the TinyGo benchmark.
//
// It initializes USB serial, prints a start message,
// and calls the benchmark function defined in this folder.
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(time.Second * 10)

	println("TinyGo Quick Sort Benchmark Starting...")
	benchmarkQuickSort()

	for {
		time.Sleep(time.Second * 10)
	}
}
