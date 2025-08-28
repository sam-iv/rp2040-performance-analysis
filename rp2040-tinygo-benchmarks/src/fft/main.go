package main

import (
	"machine"
	"math"
	"time"
)

// benchmarkFFT runs an FFT benchmark on a fixed-size sine wave input.
//
// This benchmark measures the performance of the radix-2 FFT algorithm
// using a real-valued sine wave signal. The input is transformed using
// an in-place FFT implementation. Results are printed in CSV format
// over USB serial output.
//
// Notes:
//   - The test array size is fixed at 128 samples.
//   - Output format: task,method,size,time_us
func benchmarkFFT() {
	const N = 128
	real := make([]float32, N)
	imag := make([]float32, N)

	// Fill input with a sine wave
	for i := 0; i < N; i++ {
		real[i] = float32(math.Sin(2 * math.Pi * float64(i) / float64(N)))
		imag[i] = 0
	}

	start := time.Now()
	fftRadix2(real, imag)
	elapsed := time.Since(start).Microseconds()

	println("task,method,size,time_us")
	println("fft,radix2,", N, ",", elapsed)
}

// main is the entry point for the TinyGo benchmark.
//
// It initializes USB serial, prints a start message,
// and calls the benchmark function defined in this folder.
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(time.Second * 10)

	println("TinyGo FFT Benchmark Starting...")
	benchmarkFFT()

	for {
		time.Sleep(time.Second * 10)
	}
}
