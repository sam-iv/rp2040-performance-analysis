package main

import (
	"machine"
	"time"
)

// createMatrix creates a square matrix of size n x n filled using a provided function.
//
// The fill function is called with the row and column indices for each cell.
func createMatrix(n int, fill func(i, j int) int) [][]int {
	mat := make([][]int, n)
	for i := range mat {
		mat[i] = make([]int, n)
		for j := range mat[i] {
			mat[i][j] = fill(i, j)
		}
	}
	return mat
}

// benchmarkMatrixMult runs a benchmark for matrix multiplication using 2D slices.
//
// This benchmark multiplies square matrices of size 10 and 20 using a basic
// triple-nested loop approach. Matrix A is filled with i+j and matrix B with i−j.
// The result is stored in matrix C, and the execution time is printed in CSV format.
//
// Output format:
//   task,method,size,time_us
func benchmarkMatrixMult() {
	sizes := []int{10, 20}
	println("task,method,size,time_us")

	for _, size := range sizes {
		A := createMatrix(size, func(i, j int) int { return i + j })
		B := createMatrix(size, func(i, j int) int { return i - j })
		C := createMatrix(size, func(i, j int) int { return 0 })

		start := time.Now()
		MatrixMultiply(size, A, B, C)
		elapsed := time.Since(start).Microseconds()

		println("matrix,multiply,", size, ",", elapsed)
	}
}

// main is the entry point for the TinyGo benchmark.
//
// It initializes USB serial, prints a start message,
// and calls the benchmark function defined in this folder.
func main() {
	machine.Serial.Configure(machine.UARTConfig{})
	time.Sleep(time.Second * 10)

	println("TinyGo Matrix Multiplication Benchmark Starting...")
	benchmarkMatrixMult()

	for {
		time.Sleep(time.Second * 10)
	}
}
