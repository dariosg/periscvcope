int factorial(int n)
{
	if (n == 0) {
		return 1;
	}

	return n * factorial(n-1);
}

volatile int val = 5;

int main()
{

  factorial(val);
  while(1);

  return 0;
}
