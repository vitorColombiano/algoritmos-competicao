#include <stdio.h>

int isPrime(unsigned int x) {
  if (x < 2) return 0;
  if (x == 2 || x == 3) return 1;
  if (x % 2 == 0) return 0;
  for (unsigned int i = 3; i * (unsigned long long)i <= x; i += 2) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}

int main(void) {
  int N;

  scanf("%d", &N);
  while(N--) {
    unsigned int X;
    scanf("%u", &X);
    if (isPrime(X))
      printf("Prime\n");
    else
      printf("Not Prime\n");
  }
}
