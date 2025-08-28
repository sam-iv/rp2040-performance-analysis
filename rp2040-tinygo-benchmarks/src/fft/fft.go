package main

import "math"

// bitReverse reorders the input slices in bit-reversed order.
//
// This rearranges the elements of the input arrays in bit-reversed index order.
// It is a common preprocessing step in radix-2 FFT implementations to prepare
// for the Cooley-Tukey algorithm.
//
// Parameters:
//   - real: slice containing the real part of the input signal.
//   - imag: slice containing the imaginary part of the input signal.
//
// Notes:
//   - Both slices must have the same length.
//   - The data is modified in place.
func bitReverse(real, imag []float32) {
	n := len(real)
	j := 0
	for i := 0; i < n; i++ {
		if i < j {
			real[i], real[j] = real[j], real[i]
			imag[i], imag[j] = imag[j], imag[i]
		}
		m := n >> 1
		for j >= m && m > 0 {
			j -= m
			m >>= 1
		}
		j += m
	}
}

// fftRadix2 computes the radix-2 FFT on real and imaginary input slices.
//
// This function implements the Cooley-Tukey radix-2 decimation-in-time FFT
// algorithm. It expects the input to be prearranged in bit-reversed order,
// and performs the in-place computation of the FFT result.
//
// Parameters:
//   - real: slice of real input samples.
//   - imag: slice of imaginary input samples (typically all zeroes).
//
// Notes:
//   - The input size must be a power of 2.
//   - The FFT is computed in place and overwrites the original input.
func fftRadix2(real, imag []float32) {
	n := len(real)
	bitReverse(real, imag)

	for s := 1; (1 << s) <= n; s++ {
		m := 1 << s
		angle := -2.0 * math.Pi / float64(m)
		wmReal := float32(math.Cos(angle))
		wmImag := float32(math.Sin(angle))

		for k := 0; k < n; k += m {
			wReal := float32(1.0)
			wImag := float32(0.0)

			for j := 0; j < m/2; j++ {
				tReal := wReal*real[k+j+m/2] - wImag*imag[k+j+m/2]
				tImag := wReal*imag[k+j+m/2] + wImag*real[k+j+m/2]

				uReal := real[k+j]
				uImag := imag[k+j]

				real[k+j] = uReal + tReal
				imag[k+j] = uImag + tImag

				real[k+j+m/2] = uReal - tReal
				imag[k+j+m/2] = uImag - tImag

				wTemp := wReal
				wReal = wReal*wmReal - wImag*wmImag
				wImag = wTemp*wmImag + wImag*wmReal
			}
		}
	}
}
