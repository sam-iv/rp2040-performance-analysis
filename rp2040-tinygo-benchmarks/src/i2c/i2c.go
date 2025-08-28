package main

import (
	"machine"
	"time"
)

// benchmarkI2C measures the average time taken to send a 4-byte message
// over I2C using the RP2040's hardware I2C0 peripheral. The test writes
// repeatedly to a slave device at address 0x42.
//
// Wiring:
//   - GPIO8 (pin 11) → SDA → GPIO8 on second Pico
//   - GPIO9 (pin 12) → SCL → GPIO9 on second Pico
//   - GND shared between devices
//
// The I2C master operates at 100 kHz and sends 100 messages to address 0x42.
// Results are printed in CSV format via USB serial.
//
// Output format:
//   task,method,iterations,total_time_us,avg_time_us
func benchmarkI2C() {
	const addr = 0x42
	const loops = 100
	data := []byte{'T', 'e', 's', 't'}

	// Configure I2C0 for 100 kHz
	machine.I2C0.Configure(machine.I2CConfig{
		SCL: machine.GPIO9,
		SDA: machine.GPIO8,
		Frequency: 100000, // 100 kHz
	})

	time.Sleep(3 * time.Second) // Allow USB serial connection

	println("Benchmark: I2C Write")
	println("task,method,iterations,total_time_us,avg_time_us")

	start := time.Now()

	for i := 0; i < loops; i++ {
		machine.I2C0.Tx(uint16(addr), data, nil)
	}

	elapsed := time.Since(start).Microseconds()
	avg := float64(elapsed) / float64(loops)

	println("i2c,write,", loops, ",", elapsed, ",", avg)
}
