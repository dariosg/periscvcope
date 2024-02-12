
enum { N = 4 };

volatile int array[N] = {0, 1, 2, 3};

int main()
{
  int res = 0;

  for(int i = 0; i < N; ++i) {
    res+=array[i];
  }

  while(1); // ensure the program terminates
  return 0;
}
