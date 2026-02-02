#include "soft_mul.h" 

int32_t soft_mul(int32_t a, int32_t b) {
	int32_t result = 0;
	int32_t sign = 1;

	// Handle signs to work with positive numbers for the shift logic
	// (This prevents issues with arithmetic vs logical shifts on negative numbers)
	if (a < 0) {
		a = -a;
		sign = -sign;
	}
	if (b < 0) {
		b = -b;
		sign = -sign;
	}

	// Russian Peasant Multiplication (Shift and Add)
	while (b > 0) {
		// If the current bit of b is 1, add a to the result
		if (b & 1) {
			result += a;
		}
		// Shift a to the left (multiply by 2)
		a <<= 1;
		// Shift b to the right (divide by 2)
		b >>= 1;
	}

	// Apply the calculated sign
	if (sign < 0) {
		result = -result;
	}

	return result;
}
