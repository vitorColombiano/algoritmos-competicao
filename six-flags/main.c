#include <stdio.h>

int main(void) {
  int N, T, D[600], P[100], instancia = 1;

  while (1) {
    scanf("%d %d", &N, &T);
    if (N == 0 && T == 0) break;

    for (int i = 0; i<N; i++) {
      scanf("%d %d", &D[i], &P[i]);
    }

    int dp[601] = {0};

    for (int t = 1; t<=T; t++) {
      for (int i = 0; i < N; i++) {
        if(t>=D[i]) {
          if(dp[t]<dp[t-D[i]]+P[i]) {
            dp[t]=dp[t-D[i]]+P[i];
          }
        }
      }
    }

    printf("Instancia %d\n", instancia++);
    printf("%d\n\n", dp[T]);
  }
}
