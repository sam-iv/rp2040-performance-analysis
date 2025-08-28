# RP2040 C Benchmarks – C vs TinyGo Performance Analysis

This repository contains the full C implementation of software and hardware benchmarks for the RP2040 microcontroller. The benchmarks are used to evaluate and compare performance against TinyGo implementations.

**Study Title**: Performance Analysis of C vs TinyGo on the RP2040 Microcontroller

## Benchmarks Implemented
### Software Benchmarks

| Task | Description |
|----------|----------|
| **Fibonacci** | Calculates the nth Fibonacci number using both iterative and recursive methods. Benchmarked at values `n = 10, 20, 30, 35` to analyze control flow and recursion impact. |
| **Bubble Sort** | A basic comparison-based sorting algorithm that repeatedly swaps adjacent elements. Tested with worst-case reverse-ordered arrays of sizes 10, 50, and 100. |
| **Quick Sort** | A divide-and-conquer sorting algorithm using Lomuto partitioning. Reverse-ordered arrays (sizes 10, 50, 100) are used to simulate worst-case performance. |
| **Loop Overhead** | Measures the baseline time of simple `for` loop execution across 1k, 10k, 100k, and 1M iterations. Useful for understanding loop control cost on RP2040. |
| **Matrix Multiplication** | Benchmarks fixed-size 2D integer matrix multiplication with matrix sizes of 10x10 and 20x20. Highlights nested loop and memory access behavior. |
| **FFT (Radix-2)** | Performs a 128-point radix-2 Cooley-Tukey FFT on a synthetic sine wave input. Evaluates floating-point performance and function call overhead. | 

### Hardware Benchmarks

| Task | Description | Pinouts Used |
|----------|----------|----------|
| **ADC Read** | Benchmarks analog read latency from GPIO26 using RP2040's built-in ADC0. | GPIO26 (Pin 31) |
| **GPIO Toggle** | Measures digital write speed by toggling a pin rapidly. | GPIO2 (Pin 4) |
| **PWM Setup** | Benchmarks time to configure and start PWM on GPIO15. Verified using buzzer and logger probe. | GPIO15 (Pin 20, buzzer output) |
| **Interrupt** | Measures latency from GPIO14 rising edge (button press) to ISR execution. Buzzer on GPIO15 confirms interrupt response. | GPIO14 (button), GPIO15 (buzzer) |
| **UART TX** | Times transmission of a short message to a second Pico acting as a UART logger. | TX: GPIO0 (Pin 1) |
| **I2C Write** | Measures I2C master write latency to a passive Pico responder at address 0x42. | SDA: GPIO8, SCL: GPIO9 |

## Folder Structure
```c_benchmarks/
├── src/                       # One folder per benchmark
│   ├── adc/benchmark.c
│   ├── gpio/benchmark.c
│   └── ...
├── include/benchmarks.h       # Function declarations
├── c_benchmarks.c             # BENCHMARK_MODE switch
├── CMakeLists.txt             # Pico SDK build config
├── run_software_benchmarks.c  # Software benchmarks dispatcher
├── results/                   # Collected CSVs
```

## Build and Run Instructions
### 1. Select a Benchmark
Open `c_benchmarks.c` and choose a benchmark by modifying the value of `BENCHMARK_MODE`:

```
#define BENCHMARK_MODE 3  // e.g., PWM benchmark
```

### 2. Build the Project
Inside the VS Code Pico SDK Environment:

```
mkdir build && cd build
cmake ..
ninja
```

(Note: This project was made using the official Raspberry Pi Pico Project VS Extension, and can be imported as one for easy compilation and flashing. More info: [Getting Started with Pico PDF](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf), see pages 8–10)

### 3. Flash to Pico
Drag and drop the generated UF2 file into the Pico while it’s in USB mass storage mode.

### 4. Open Serial Monitor
View CSV Output:

```
task,method,size,time_us
bubblesort,bubble,50,4801
```

## Output Format

All benchmarks output structured CSV lines for use in:

- Analysis and comparison (C vs TinyGo)
- Table generation for report
- Graph plotting (Python, Excel, etc.)

Each benchmark prints relevant fields like:
- task, method, size/iteration, time_us

## Benchmarking Methodology

Each benchmark was compiled and executed in complete isolation to ensure fair and reproducible measurement of runtime performance, binary size, and memory usage.

This procedure ensures that:
- Only the selected benchmark function is compiled and linked
- Memory footprint (.elf, .map, .S) reflects just that benchmark
- No external code paths interfere with runtime results

All benchmarks were executed five times. Raw CSV outputs were stored in `results/raw/` and summarised in `results/summary/` for comparison.

### How Benchmarks Were Isolated

To isolate each benchmark:

1. Replace the benchmark function call in `main()` (e.g., `benchmark_fibonacci();`)
2. In `CMakeLists.txt`, comment out all unused `.c` files under `add_executable()`
3. Run a clean build:
   ```bash
   cmake --build . --clean-first
   ```
4. Capture results:
   - Timing output → `results/raw/`
   - ~~Memory footprint → `results/memory/` (via `.txt`, `.map`, `.disasm.S`)~~ Removed

A reproducible example is provided in [`examples/example_individual_run.c`](./examples/example_individual_run.c).

## Dependencies

To build and run this project, ensure the following tools are installed:

### Required
- Raspberry Pi Pico board (or RP2040-compatible board)
- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- CMake ≥ 3.13
- `gcc-arm-none-eabi` toolchain
- `ninja` or `make`
- USB cable (Micro USB)

### Recommended (especially for Windows/macOS)
- [Zadig](http://zadig.akeo.ie/) – USB CDC driver installer
- [PuTTY](https://www.putty.org/) or VS Code Serial Monitor – for reading serial output
- [Picotool](https://github.com/raspberrypi/picotool) – optional binary inspection tool

### Optional
- Visual Studio Code + Raspberry Pi Pico Extension
  - Simplifies building/flashing/viewing serial output
  - See [Getting Started with Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

## Related Projects
- [TinyGo Benchmarks](../rp2040-tinygo-benchmarks/) - TinyGo equivalents
- [Tools](../tools/) - GPIO probe, UART Logger, I2C responder

