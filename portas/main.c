#include <stdio.h>
#include <math.h>

int main() {
  int N;
  while (scanf("%d", &N) && N != 0) {
    int k = sqrt(N);
    for (int i = 1; i <= k; i++) {
      printf("%d", i*i);
      if (i < k) printf(" ");
    }
    printf("\n");
  }
  return 0;
}
