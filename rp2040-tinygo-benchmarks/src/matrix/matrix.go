package main

// MatrixMultiply performs matrix multiplication on two square matrices.
//
// This function multiplies matrices A and B (both size x size) and stores
// the result in matrix C. All matrices must be preallocated with dimensions [size][size].
//
// Parameters:
//   - size: dimension of the square matrices
//   - A: input matrix A
//   - B: input matrix B
//   - C: output matrix C where the result is stored
func MatrixMultiply(size int, A, B, C [][]int) {
	for i := 0; i < size; i++ {
		for j := 0; j < size; j++ {
			sum := 0
			for k := 0; k < size; k++ {
				sum += A[i][k] * B[k][j]
			}
			C[i][j] = sum
		}
	}
}
