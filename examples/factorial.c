#include <soft_mul.h>

#include <stdint.h>

int32_t factorial(int32_t n)
{
	if (n == 0) {
		return 1;
	}

	int fact_n_1 = factorial(n-1);

	return soft_mul(n, fact_n_1);
}

volatile int32_t val = 5;

int main()
{

  factorial(val);
  while(1);

  return 0;
}
