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
# ==========================================================================================

cmake_minimum_required(VERSION 3.13)

# Project Metadata
project(rp2040_tools C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Board and SDK
set(PICO_BOARD pico CACHE STRING "Board type")
include(pico_sdk_import.cmake)
pico_sdk_init()

# Executable Source Files
add_executable(rp2040_tools
    tools.c

    # Tool Implementations (each mode is modular)
    gpio_probe/probe.c
    uart_logger/uart_logger.c
    i2c_responder/responder.c
)

# Fix: Ensure output has a valid .elf extension for picotool
set_target_properties(rp2040_tools PROPERTIES OUTPUT_NAME "rp2040_tools.elf")

# Executable Metadata
pico_set_program_name(rp2040_tools "rp2040_tools")
pico_set_program_version(rp2040_tools "0.1")

# USB Serial (UART disabled)
pico_enable_stdio_uart(rp2040_tools 0)
pico_enable_stdio_usb(rp2040_tools 1)

# Required Libraries
target_link_libraries(rp2040_tools
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_timer
    hardware_clocks
)

# Include Directories
target_include_directories(rp2040_tools PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Final Build Outputs (UF2, bin, disasm, etc.)
pico_add_extra_outputs(rp2040_tools)
