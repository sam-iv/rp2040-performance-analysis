package main

// BubbleSort performs an in-place Bubble Sort on an integer slice.
//
// Sorts a slice using the classic Bubble Sort algorithm,
// which repeatedly compares and swaps adjacent elements until the
// slice is fully ordered.
//
// Arrays are expected to be pre-filled before calling this function.
// This is a worst-case simulation when the input is reverse-ordered.
//
// Time complexity: O(n²) in the worst case.
//
// Parameters:
//   - arr: slice of integers to be sorted
func BubbleSort(arr []int) {
	n := len(arr)
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
			}
		}
	}
}
