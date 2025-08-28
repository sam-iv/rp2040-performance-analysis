package common

import "time"

// MeasureUS measures the execution time of the given function in microseconds.
//
// The provided function `fn` is executed once, and the duration from start to
// finish is returned as an int64 in microseconds.
//
// Parameters:
//   - fn: the function to benchmark
//
// Returns:
//   - Execution time in microseconds
func MeasureUS(fn func()) int64 {
	start := time.Now()
	fn()
	return time.Since(start).Microseconds()
}
