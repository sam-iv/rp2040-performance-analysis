# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# ================================
# CMake Project: c_benchmarks
# RP2040 Benchmark Suite (C)
# ================================

cmake_minimum_required(VERSION 3.13)

# C Standard & Build Info
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------------------------------
# Optimisation Level
# ----------------------------------------------------

# By default, the build type is set to "Release" meaning
# the optimisation level is set to "Release" (i.e., -O2).

# ----------------------------------------------------

set(PICO_BOARD pico CACHE STRING "Board type")
include(pico_sdk_import.cmake)

# Project Declaration
project(c_benchmarks C CXX ASM)
pico_sdk_init()

# ----------------------------------------------------
# Executable & Source Files
# ----------------------------------------------------
add_executable(c_benchmarks
    c_benchmarks.c
    run_software_benchmarks.c

    # Software benchmarks
    src/fibonacci/benchmark.c
    src/bubblesort/benchmark.c
    src/quicksort/benchmark.c
    src/loop/benchmark.c
    src/matrix/benchmark.c
    src/fft/benchmark.c

    # Hardware benchmarks
    src/adc/benchmark.c
    src/gpio/benchmark.c
    src/pwm/benchmark.c
    src/interrupt/benchmark.c
    src/uart/benchmark.c
    src/i2c/benchmark.c
)

pico_set_program_name(c_benchmarks "c_benchmarks")
pico_set_program_version(c_benchmarks "0.1")

# ----------------------------------------------------
# USB Serial Output (UART disabled)
# ----------------------------------------------------
pico_enable_stdio_uart(c_benchmarks 0)
pico_enable_stdio_usb(c_benchmarks 1)

# ----------------------------------------------------
# Include Directories
# ----------------------------------------------------
target_include_directories(c_benchmarks PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# ----------------------------------------------------
# Link Required Pico Libraries
# ----------------------------------------------------
target_link_libraries(c_benchmarks
    pico_stdlib
    hardware_timer
    hardware_adc
    hardware_pwm
    hardware_i2c
    m
)

# ----------------------------------------------------
# Additional Output Files (e.g., .uf2)
# ----------------------------------------------------
pico_add_extra_outputs(c_benchmarks)
