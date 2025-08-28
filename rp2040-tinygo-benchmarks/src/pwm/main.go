package main

import (
	"machine"
	"time"
)

// main runs the PWM setup time benchmark for RP2040.
//
// This benchmark measures the time taken to configure and start
// a PWM signal on a designated GPIO pin using the RP2040's hardware PWM peripheral.
//
// Wiring:
//   - GPIO15 (pin 20) → Positive terminal of buzzer and/or probe input
//   - Buzzer GND → Common GND rail
//
// It does not measure waveform timing accuracy, but rather the latency of setup
// and activation. The signal can be verified using a buzzer or a second Pico logic probe.
//
// Output format:
//   task,method,setup_time_us
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(10 * time.Second) // Allow USB serial monitor to connect

	println("TinyGo PWM Benchmark Starting...")
	println("Benchmark: PWM Setup")
	println("task,method,setup_time_us")

	const pwmPin = machine.GPIO15 // GPIO15 = physical pin 20

	pwm := machine.PWM7 // GPIO15 maps to PWM7

	start := time.Now()

	err := pwm.Configure(machine.PWMConfig{
		Period: 8200, // ~122 kHz for audible buzzer tone
	})
	if err != nil {
		println("pwm,error,", err.Error())
		return
	}

	ch, err := pwm.Channel(pwmPin)
	if err != nil {
		println("pwm,error,", err.Error())
		return
	}

	pwm.Set(ch, pwm.Top()/2) // 50% duty cycle

	elapsed := time.Since(start).Microseconds()
	println("pwm,setup,", elapsed)

	for {
		time.Sleep(time.Second)
	}
}
