package main

import (
	"machine"
	"time"
)

// benchmarkLoopOverhead runs a benchmark to measure basic loop iteration overhead.
//
// This benchmark uses a global counter and executes for-loops with a fixed number
// of iterations (1K to 1M). Results are printed in CSV format to evaluate the
// raw overhead of loop control logic in TinyGo.
//
// Output format:
//   task,method,iterations,time_us[,result]
func benchmarkLoopOverhead() {
	iterations := []int{1000, 10000, 100000, 1000000}
	println("task,method,iterations,time_us")

	for _, n := range iterations {
		start := time.Now()
		result := LoopN(n) // use the result to prevent optimisation
		elapsed := time.Since(start).Microseconds()

		println("loop,for_loop,", n, ",", elapsed, ",", "result:", result)
	}
}

// main is the entry point for the TinyGo benchmark.
//
// It initializes USB serial, prints a start message,
// and calls the benchmark function defined in this folder.
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(time.Second * 10) // allow serial monitor to connect

	println("TinyGo Loop Overhead Benchmark Starting...")
	benchmarkLoopOverhead()

	for {
		time.Sleep(time.Second * 10)
	}
}
