/**
 * @file tool_functions.h
 * @brief Function declarations for all tool modes used in the RP2040 Tools project.
 *
 * This header provides the interface for all tool functions selectable via TOOL_MODE
 * in `tools.c`. Each tool represents a standalone firmware for a secondary Pico used
 * in the C vs TinyGo benchmarking project.
 *
 * Tool Modes:
 *   - 1: GPIO Probe
 *   - 2: UART Logger
 *   - 3: I2C Responder
 *
 * These tools enable timing verification, serial inspection, and protocol validation
 * when used alongside the main benchmarking RP2040.
 *
 * @author Samuel Ivuerah
 */

#ifndef TOOL_FUNCTIONS_H
#define TOOL_FUNCTIONS_H

/**
 * @brief GPIO edge logger (Tool Mode 1).
 *
 * Continuously monitors GPIO2 and logs rising/falling edges with timestamps.
 * Used to validate toggling or PWM signals.
 */
void run_gpio_probe(void);

/**
 * @brief UART receiver/logger (Tool Mode 2).
 *
 * Listens on GPIO1 (UART RX) and prints received characters to USB serial.
 * Used to validate UART output from the main Pico.
 */
void run_uart_logger(void);

/**
 * @brief Passive I2C responder (Tool Mode 3).
 *
 * Acknowledges I2C writes sent to address 0x42 over GPIO8/9.
 * Used to benchmark I2C master write timing from the main Pico.
 */
void run_i2c_responder(void);

#endif  // TOOL_FUNCTIONS_H
