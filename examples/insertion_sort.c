#include <stdint.h>

/**
 *  * Perform Insertion Sort on a static array.
 *   * * @param arr Pointer to the array to sort
 *    * @param n   Number of elements in the array
 *     */
void insertion_sort(int32_t *arr, uint32_t n) {
	int32_t key;
	int32_t j; // Using int8_t because j can become -1

	// Start from the second element (index 1)
	for (uint32_t i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

enum {ARR_SIZE= 10};
int main(void)
{
	static int32_t data[ARR_SIZE] = {
		45, 12, 89, 7, 23, 1, 67, 99, 15, 3
	};
	insertion_sort(data, ARR_SIZE);

	while (1) {
		__asm("nop"); 
	}

	return 0;
}
