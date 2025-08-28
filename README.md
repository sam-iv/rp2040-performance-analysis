# Performance Analysis of C vs TinyGo on the RP2040 Microcontroller

This repository contains all code and resources from my final year dissertation, which performed a detailed performance analysis of [C](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html) vs [TinyGo](https://tinygo.org/) on the RP2040 microcontroller. The project evaluated each language's suitability for embedded systems development by benchmarking core software tasks and real-time peripheral interactions.

**Study Title:** Performance Analysis of C vs TinyGo on the RP2040 Microcontroller

**Dissertation:** [Click me](Dissertation.pdf)

![Hardware Benchmarks](hardware_benchmarks.png)

## Key Findings

The study found a clear trade-off between the two languages:

* **Execution Speed**: C outperformed TinyGo in 10/12 benchmarks. For latency-sensitive benchmarks such as Interrupt Handling, C was up to 5x Faster.

* **Memory Efficiency**: TinyGo consistenly produced smaller binaries (3.4x smaller on average) and used less RAM (3.5x less on average) than C. **Note**: More researched should be done here, especially with different optimisation flags for their respective compilers.

* **Performance Stability**: TinyGo exhibited lower timing jitter in 9/12 benchmarks, hence, had more predictable execution for less time-critical applications.

## Repository Structure

The project is divided into three main components, each in its own sub-directory:

* [`c-benchmarks/`](rp2040-c-benchmarks/) - The C implementation of all software and hardware benchmarks.
* [`tinygo-benchmarks/`](rp2040-tinygo-benchmarks/) - The TinyGo implementation of all software and hardware benchmarks.
* [`tools/`](tools/) - External C firmware for a secondary pico used as a hardware probe, logger, and responder.

## Methodology

A suite of 12 benchmarks was created, covering computation algorithms such as 'Quick Sort, FFT' and real-time hardware interactions like 'GPIO, PWM'.

Aspects:

* **Dual-Pico Architecture**: A test pico ran the benchmarks, a secondary probe pico provided supplemental signal observation without interfering with primary timing.

* **Disassembly Analysis**: Machine code was inspected to give an insight into the preformance variations.

* **Reproducibility**: All benchmarks were ran in a controlled environment and output standardised CSV data for analysis

## Key Takeaways

My recommendations:

* Use C for performance-critical tasks and low-latency peripheral control.

* Use TinyGo for rapid prototyping, educational use, or applications prioritising code simplicity.

* Consider hybrid architectures where each language is used where its strengths reside.

