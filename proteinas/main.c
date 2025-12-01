#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define BASE 131
#define MOD 1000000007

char dna[MAXN], prot[MAXN];
unsigned long long hash_dna[MAXN], pow_base[MAXN];
unsigned long long hash_prot[MAXN];

int main() {
  int N, M;

  scanf("%d %d", &N, &M);
  scanf("%s", dna+1);
  scanf("%s", prot+1);

  // Processa potências
  pow_base[0] = 1;
  for (int i = 1; i <= N; i++)
    pow_base[i] = pow_base[i-1] * BASE;

  // Preprocessa hash do DNA
  hash_dna[0] = 0;
  for (int i = 1; i <= N; i++)
    hash_dna[i] = hash_dna[i-1] * BASE + dna[i];

  // Preprocessa hash da proteína
  hash_prot[0] = 0;
  for (int i = 1; i <= M; i++)
    hash_prot[i] = hash_prot[i-1] * BASE + prot[i];

  int Q;
  scanf("%d", &Q);
  while (Q--) {
    
  }

  return 0;
}
