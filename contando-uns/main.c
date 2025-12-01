#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long memo[65][2][65];

long long contaUnsRec(int pos, int restrito, int total_uns, int bin[], int tamanho) {
  if (pos == tamanho) return total_uns;
  if (memo[pos][restrito][total_uns] != -1) return memo[pos][restrito][total_uns];
  long long resposta = 0;
  int limite = restrito ? bin[pos] : 1;
  for (int digito = 0; digito <= limite; digito++) {
    resposta += contaUnsRec(pos + 1, restrito && (digito == limite), total_uns + (digito == 1), bin, tamanho);
  }
  memo[pos][restrito][total_uns] = resposta;
  return resposta;
}


long long countUns(long long N) {
  int bin[65], tamanho = 0;
  for (int i = 63; i >= 0; i--) {
    bin[tamanho++] = (N >> i) & 1;
  }

  memset(memo, -1, sizeof(memo));
  return contaUnsRec(0, 1, 0, bin, tamanho);
}

int main() {
  long long A, B;
  while(scanf("%lld %lld", &A, &B) == 2) {
    long long resultado = countUns(B) - countUns(A-1);
    printf("%lld\n", resultado);
  }

  return 0;
}
