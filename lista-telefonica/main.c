#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_L 201

char telefones[MAX_N][MAX_L];

int compare(const void *a, const void *b) {
  return strcmp((char *)a, (char *)b);
}

int main() {
  int N;
  while (scanf("%d", &N) != EOF) {
    for (int i = 0; i < N; i++) {
      scanf("%s", telefones[i]);
    }

    qsort(telefones, N, MAX_L, compare);

    long long economia = 0;
    for (int i = 1; i < N; i++) {
      int prefixo = 0;
      while (telefones[i][prefixo] != '\0' &&
             telefones[i][prefixo] == telefones[i-1][prefixo]) {
        prefixo++;
      }
      economia += prefixo;
    }

    printf("%lld\n", economia);
  }
  return 0;
}
