# RP2040 TinyGo Benchmarks – C vs TinyGo Performance Analysis

This repository contains the full TinyGo implementation of software and hardware benchmarks for the RP2040 microcontroller. The benchmarks are used to evaluate and compare performance against C implementations.

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
| **GPIO Toggle** | Measures digital write speed by toggling a pin rapidly. Captured using a second Pico as a logic probe. | GPIO2 (Pin 4) |
| **PWM Setup** | Benchmarks time to configure and start PWM on GPIO15. Verified using buzzer and logger probe. | GPIO15 (Pin 20, buzzer output) |
| **Interrupt** | Measures latency from GPIO14 rising edge (button press) to ISR execution. Buzzer on GPIO15 confirms interrupt response. | GPIO14 (button), GPIO15 (buzzer) |
| **UART TX** | Times transmission of a short message to a second Pico acting as a UART logger. | TX: GPIO0 (Pin 1) |
| **I2C Write** | Measures I2C master write latency to a passive Pico responder at address 0x42. | SDA: GPIO8, SCL: GPIO9 |

## Folder Structure

```
tinygo_benchmarks/
├── src/              # All benchmark folders live here (e.g., adc, fft, quicksort...)
├── build/            # Compiled UF2 binaries
├── results/          # Raw & summary CSV logs
├── build.bat         # Optional Windows builder script
```

## Build and Run Instructions

### Option 1: Use the Batch Script (Windows Only)

Use the `build.bat` script to compile and generate UF2 binaries interactively:

```
cd tinygo_benchmarks
.\build.bat
```

Choose a benchmark by number and it will compile that folder to `build/<name>.uf2`.

### Option 2: Manual Build (Any Platform)

Use the TinyGo CLI:

```
tinygo build -target pico -o build/<benchmark>.uf2 ./src/<benchmark>
```

For example:

```
tinygo build -target pico -o build/fft.uf2 ./src/fft
```

### Flash to Pico

Drag and drop the `.uf2` file into the Pico while it is in USB mass storage mode.

Alternatively, you can use TinyGo’s built-in flash command to compile and upload in one step:

```bash
tinygo flash -target pico ./src/fft
```

> This works when your Pico is in BOOTSEL mode and mounted as a USB device. TinyGo will automatically build and flash the binary to your board.

## Output Format

All benchmarks output structured CSV lines that can be used for:

- Comparison with C results
- Plotting graphs
- Spreadsheet import

Example output:

```
task,method,size,time_us
bubblesort,bubble,50,4821
```

Each output includes:

- `task`: name of the benchmark
- `method`: algorithm or technique used
- `size`: input size or loop count
- `time_us`: execution time in microseconds

## Benchmarking Methodology

Each TinyGo benchmark was built and run in isolation to ensure fair comparison with C results.

This ensures:

- Only the selected benchmark is included in the final binary
- No other functions affect timing
- Memory footprint remains specific to that test

Each benchmark was executed 5 times. The results were:

- Saved to `results/raw/` as CSV
- Summarised in `results/summary/` for analysis

### How Benchmarks Were Isolated

To isolate each benchmark:

1. Navigate to the repo root
2. Run:
   ```
   .\build.bat
   ```
3. Select the relevant benchmark by number
4. Flash the resulting `.uf2` to your Pico
5. Use a serial monitor to capture and save the output

### Memory and Code Size Analysis

Each TinyGo `.elf` binary was analyzed using the following LLVM tools:

```bash
llvm-size -A build/<benchmark>.elf    > results/memory/<benchmark>.txt

llvm-nm -S build/<benchmark>.elf      > results/memory/<benchmark>.map

llvm-objdump -d build/<benchmark>.elf > results/memory/<benchmark>.disasm.S
```
**Note:** The Memory folder has been removed

These files were used to evaluate:
- Code size
- RAM usage
- Symbol layout
- Static disassembly for complexity inspection

## Dependencies

### Required
- Raspberry Pi Pico or RP2040-based board
- [TinyGo](https://tinygo.org/getting-started/) ≥ 0.37
- Go toolchain (installed by TinyGo or manually)
- USB cable (Micro USB)

### Recommended (especially for Windows/macOS)
- [Zadig](http://zadig.akeo.ie/) – USB CDC driver installer
- [PuTTY](https://www.putty.org/) or VS Code Serial Monitor
- [VS Code + TinyGo Extension](https://marketplace.visualstudio.com/items?itemName=tinygo.vscode-tinygo)

## Related Projects

- [C Benchmarks](../rp2040-c-benchmarks/) – C equivalents of all benchmarks
- [Tools](../tools/) – Support tools: GPIO logger, UART listener, I2C responder
