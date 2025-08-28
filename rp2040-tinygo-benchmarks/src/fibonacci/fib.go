package main

// FibIterative computes the nth Fibonacci number using an iterative loop.
//
// This approach avoids recursion by maintaining only the last two computed values.
// It is more efficient than the recursive version, especially for large n.
//
// Parameters:
//   - n: index of the Fibonacci number to compute (0-based)
//
// Returns:
//   - The nth Fibonacci number
func FibIterative(n int) int {
	if n <= 1 {
		return n
	}
	prev, curr := 0, 1
	for i := 2; i <= n; i++ {
		prev, curr = curr, prev+curr
	}
	return curr
}

// FibRecursive computes the nth Fibonacci number using recursion.
//
// This function uses a straightforward recursive approach where each call
// computes fib(n-1) + fib(n-2). It is conceptually simple but inefficient
// due to repeated subcomputations.
//
// Parameters:
//   - n: index of the Fibonacci number to compute (0-based)
//
// Returns:
//   - The nth Fibonacci number
func FibRecursive(n int) int {
	if n <= 1 {
		return n
	}
	return FibRecursive(n-1) + FibRecursive(n-2)
}
