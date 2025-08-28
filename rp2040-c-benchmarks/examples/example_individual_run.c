/**
 * @file example_individual_run.c
 * @brief Example of how a single benchmark is isolated and compiled for clean measurement.
 *
 * This minimal `main()` function shows how each benchmark was run independently
 * during the evaluation phase. This approach ensures that memory usage,
 * binary size, and runtime results only reflect the selected benchmark.
 *
 * Steps for reproducible measurement:
 * 1. Swap the benchmark call inside `main()` (e.g., `benchmark_fibonacci();`)
 * 2. In `CMakeLists.txt`, **comment out all other source files** under `add_executable()`
 *    except the one being tested (e.g., `src/fibonacci/benchmark.c`)
 * 3. Rebuild with `cmake --build . --clean-first`
 * 4. Collect runtime + memory metrics
 *
 * This method was used for:
 *   - Flash/RAM usage (.elf, .map, .S files)
 *   - Runtime timing (CSV output)
 *
 * @author Samuel Ivuerah
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "benchmarks.h"

int main() {
    stdio_init_all();
    sleep_ms(10000);  // Allow USB serial to initialise

    printf("Benchmark Mode: Fibonacci\n");
    printf("--------------------------\n");

    benchmark_fibonacci();  // Swap this line per benchmark
}
