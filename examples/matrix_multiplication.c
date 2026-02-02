#include <stdint.h>

#include <soft_mul.h>

enum {SZ =4 };

void mat_mul_4x4(int32_t A[SZ][SZ], int32_t B[SZ][SZ], int32_t C[SZ][SZ]) {
	for (int32_t i = 0; i < SZ; i++) {           // Iterate rows of A
		for (int32_t j = 0; j < SZ; j++) {       // Iterate columns of B
			int32_t sum = 0;
			for (int32_t k = 0; k < SZ; k++) {   // Iterate shared dimension
				int32_t product = soft_mul(A[i][k], B[k][j]);
				sum += product;
			}
			C[i][j] = sum;
		}
	}
}

int32_t MatrixA[SZ][SZ] = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 1, 2, 3},
	{4, 5, 6, 7}
};

int32_t MatrixB[SZ][SZ] = {
	{2, 0, 0, 0},
	{0, 2, 0, 0},
	{0, 0, 2, 0},
	{0, 0, 0, 2}
};

int32_t MatrixC[SZ][SZ];

int main() {
  mat_mul_4x4(MatrixA, MatrixB, MatrixC);

  while(1) {
    asm volatile("nop"); 
  }
  return 0;
}
