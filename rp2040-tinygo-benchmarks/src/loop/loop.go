package main

// LoopN runs a simple for-loop N times and increments a global counter.
//
// This function is used to benchmark loop overhead in TinyGo by executing
// a fixed number of loop iterations. The result is stored in a global sink
// to prevent the compiler from optimizing the loop away.
//
// Parameters:
//   - n: the number of loop iterations to perform
//
// Returns:
//   - The final value of the global LoopSink after execution
var LoopSink int

func LoopN(n int) int {
	for i := 0; i < n; i++ {
		LoopSink++
	}
	return LoopSink
}
