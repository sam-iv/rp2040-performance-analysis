package main

// QuickSort performs an in-place quicksort on the given array.
//
// This function sorts the sub-array of arr between indices low and high
// using the recursive divide-and-conquer approach with Lomuto partitioning.
//
// Parameters:
//   - arr: the array to sort
//   - low: the starting index
//   - high: the ending index
func QuickSort(arr []int, low, high int) {
	if low < high {
		p := partition(arr, low, high)
		QuickSort(arr, low, p-1)
		QuickSort(arr, p+1, high)
	}
}

// partition rearranges elements in the array based on a pivot.
//
// Elements less than the pivot are moved before it, and elements greater
// are moved after. Returns the index of the pivot after partitioning.
func partition(arr []int, low, high int) int {
	pivot := arr[high]
	i := low - 1
	for j := low; j < high; j++ {
		if arr[j] < pivot {
			i++
			arr[i], arr[j] = arr[j], arr[i]
		}
	}
	arr[i+1], arr[high] = arr[high], arr[i+1]
	return i + 1
}
