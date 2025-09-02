#include <stdio.h>
#define NUM 10

int main() {
  int V, N;
  scanf("%d %d", &V, &N);

  if (V < 1 || N > 10000) return 0;

  int total = V*N;

  for (int i = 1; i < NUM; i++) {
    int porcentagem = (total * i + 9)/10;
    if (i == NUM - 1) {
      printf("%d\n", porcentagem);
      break;
    }
    printf("%d ", porcentagem);
  }
  
  return 0;
}
