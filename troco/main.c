#include <stdio.h>

int main(void) {
  int V, M, moedas[1000];
  scanf("%d %d", &V, &M);

  for (int i=0; i < M; i++) {
    scanf("%d", &moedas[i]);
  }

  char dp[100001] = {0};
  dp[0] = 1;

  for (int i = 0; i < M; i++) {
    for (int v = V; v >= moedas[i]; v--) {
      if (dp[v - moedas[i]]) dp[v] = 1;
    }
  }

  printf("%s\n", dp[V] ? "S" : "N");
  return 0;
}