package main

import (
	"machine"
	"time"
)

// benchmarkADC measures the latency of ADC reads on GPIO26 (ADC0).
//
// This function performs 1000 ADC reads, measures the time for each read, 
// and calculates the average read time in microseconds. Selected sample 
// values are printed for verification purposes.
//
// Wiring:
//   - GPIO26 (pin 31) → Wiper (middle pin) of potentiometer
//   - 3.3V            → One side of potentiometer
//   - GND             → Other side of potentiometer
//
// Output format:
//   task,method,reads,avg_time_us
func benchmarkADC() {
	const samples = 1000

	// Initialize ADC subsystem and GPIO26 (ADC0)
	machine.InitADC()

	// Set up ADC for GPIO26 (ADC0)
	adc := machine.ADC{Pin: machine.ADC0}
	adc.Configure(machine.ADCConfig{})

	// Print the header for CSV output
	println("task,method,reads,avg_time_us")

	var totalTime int64

	// Perform 1000 ADC reads, timing each operation individually
	for i := 0; i < samples; i++ {
		start := time.Now()
		val := adc.Get()  // Perform a single ADC read
		elapsed := time.Since(start).Microseconds()  // Measure the time taken in microseconds
		totalTime += elapsed

		// Print selected sample values for verification every 250th read
		if i%250 == 0 {
			println("adc,sample,", i, ",", val)
		}
	}

	// Calculate the average time taken for a single read and print it
	avg := totalTime / int64(samples)
	println("adc,single_read,", samples, ",", avg)
}
