#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  if (n < 2 || n > 10000) return 0;

  int votos[10000];
  for (int i = 0; i < n; i++) {
      scanf("%d", &votos[i]);
  }

  int maior = votos[0];
  for (int i = 1; i < n; i++) {
      if (votos[i] > maior) {
          maior = votos[i];
      }
  }

  if (votos[0] == maior) {
      printf("S\n");
      return 0;
  }

  printf("N\n");
  return 0;
}
