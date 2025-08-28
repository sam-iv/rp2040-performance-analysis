# RP2040 Tools Repository – Support Utilities for Benchmarking

This repository contains all utility firmware used to assist the C vs TinyGo benchmarking project on the Raspberry Pi Pico (RP2040). Each utility runs standalone on a secondary Pico and acts as a probe, logger, or responder to help measure hardware performance metrics during benchmarking.

**Study Title**: *Performance Analysis of C vs TinyGo on the RP2040 Microcontroller*

---

## Tool Modes Implemented

Each tool is selected by setting `TOOL_MODE` in `tools.c`:

| Mode | Tool Name      | Description                                                                 |
|------|----------------|-----------------------------------------------------------------------------|
| 1    | GPIO Probe     | Logs GPIO2 transitions with microsecond timestamps. Verifies toggling or PWM signals. |
| 2    | UART Logger    | Listens on GPIO1 and prints received characters. Confirms UART TX.          |
| 3    | I2C Responder  | Acts as passive I2C slave at address 0x42. Confirms master writes from another Pico. |

---

## Folder Structure

```bash
tools/
├── gpio_probe/           # TOOL_MODE 1 source (probe)
│   └── probe.c
├── uart_logger/          # TOOL_MODE 2 source (UART RX)
│   └── logger.c
├── i2c_responder/        # TOOL_MODE 3 source (I2C responder)
│   └── responder.c
├── include/
│   └── tool_functions.h  # Declarations for all tool functions
├── tools.c               # Entry point with TOOL_MODE switch
├── CMakeLists.txt        # Pico SDK project setup
```

---

## Build and Run Instructions

### 1. Select a Tool Mode
Edit `tools.c`:
```c
#define TOOL_MODE 2  // UART Logger
```

### 2. Build the Project
Inside the VS Code Pico SDK Environment:
```bash
mkdir build && cd build
cmake ..
ninja
```

(Note: This project was built using the official Raspberry Pi Pico VS Code Extension. It can be imported as a Pico project for easy compilation and flashing. For setup, refer to the [Getting Started with Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) guide, pages 8–10.)

### 3. Flash to Pico
Copy the `tools.uf2` file to your secondary Pico while in bootloader mode.

### 4. Open Serial Monitor
You will see:
```
Tool Mode: 2
----------------------
UART Logger Ready (RX on GPIO1)
```

---

## Output Format

Each tool prints a startup banner and then begins capturing hardware behaviour. Sample logs include:
- `timestamp_us,state` for GPIO edge probe
- Characters received for UART logger
- Silent acknowledgment for I2C (can be extended to print if desired)

---

## Pinout Summary

| Tool Mode | Signal         | GPIO Pin | Notes                                 |
|-----------|----------------|----------|---------------------------------------|
| 1         | Probe Input    | GPIO2    | Connect to GPIO under test (e.g. PWM) |
| 2         | UART RX        | GPIO1    | Main Pico TX = GPIO0                  |
| 3         | I2C SDA / SCL  | GPIO8/9  | Connect to I2C master Pico            |

---

## Benchmarking Methodology

These tools were used to validate the correctness of hardware output from the main benchmarking Pico. Each one was flashed to a dedicated secondary Pico and monitored via serial.

Tools confirmed:
- **GPIO toggling** timing consistency and waveform spacing
- **PWM signal** duty cycles and activation
- **UART TX** throughput and character reliability
- **I2C master** write acknowledgment

Only one tool runs at a time. The tool mode is chosen in `tools.c` and compiled using the shared build system.

---

## Dependencies

To build and use the tools, you need:

### Required
- Raspberry Pi Pico board (RP2040)
- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- CMake ≥ 3.13
- ARM GCC toolchain (`arm-none-eabi-gcc`)
- `ninja` or `make`

### Recommended (especially for Windows/macOS)
- [Zadig](http://zadig.akeo.ie/) – USB CDC driver installer
- [PuTTY](https://www.putty.org/) or VS Code Serial Monitor – for reading serial output
- [Picotool](https://github.com/raspberrypi/picotool) – optional binary inspection tool

### Optional
- Visual Studio Code + Raspberry Pi Pico Extension
  - Simplifies building, flashing, and viewing serial output
  - See [Getting Started with Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

---

## Related Projects
\- [C Benchmarks](../rp2040-c-benchmarks/) – C benchmark suite for performance testing
- [TinyGo Benchmarks](../rp2040-tinygo-benchmarks/) – TinyGo equivalents for cross-comparison
