package main

import (
	"machine"
	"time"
)

// benchmarkFibonacci runs Fibonacci benchmarks on a predefined set of values.
//
// This benchmark tests both iterative and recursive implementations of the
// Fibonacci sequence. Execution time is measured using high-resolution timers,
// and the results are printed in CSV format over USB serial.
//
// Tested values: 10, 20, 30, 35
// Output format: task,method,n,result,time_us
func benchmarkFibonacci() {
	ns := []int{10, 20, 30, 35}

	println("task,method,n,result,time_us")

	for _, n := range ns {
		// Iterative
		start := time.Now()
		result := FibIterative(n)
		elapsed := time.Since(start).Microseconds()
		println("fibonacci,iterative,", n, ",", result, ",", elapsed)

		// Recursive
		start = time.Now()
		result = FibRecursive(n)
		elapsed = time.Since(start).Microseconds()
		println("fibonacci,recursive,", n, ",", result, ",", elapsed)
	}
}

// main is the entry point for the TinyGo benchmark.
//
// It initializes USB serial, prints a start message,
// and calls the benchmark function defined in this folder.
func main() {
	// Configure USB serial output and wait for host to connect
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(time.Second * 10)

	println("TinyGo Fibonacci Benchmark Runner Starting...")
	benchmarkFibonacci()

	for {
		time.Sleep(time.Second * 5)
	}
}
