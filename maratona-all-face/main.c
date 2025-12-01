#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 1000000007
#define MAXN 100005

char is_prime[MAXN];
int primes[MAXN], nprimes = 0;

void crivo() {
  for (int i = 2; i < MAXN; i++) is_prime[i] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (is_prime[i]) {
      primes[nprimes++] = i;
      for (int j = i + i; j < MAXN; j += i) {
        is_prime[j] = 0;
      }
    }
  }
}

long long modpow(long long base, long long exp) {
  long long res = 1;
  while (exp) {
    if (exp & 1) res = (res * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return res;
}

long long geom_sum(long long p, long long e) {
  if (e == 0) return 1;
  if (p == 1) return (e + 1) % MOD;
  long long num = (modpow(p, e + 1) - 1 + MOD) % MOD;
  long long den = (p - 1 + MOD) % MOD;
  long long inv = modpow(den, MOD - 2);
  return (num * inv) % MOD;
}

int main() {
  crivo();
  int N;
  while(scanf("%d", &N) == 1) {
    long long sum_div = 1;
    long long fact = 1;
    for(int i = 0; i < nprimes && primes[i] <= N; i++) {
      int p = primes[i];
      int exp = 0;
      int temp = N;

      while(temp) {
        exp += temp / p;
        temp /= p;
      }
      sum_div = (sum_div * geom_sum(p, exp)) % MOD;
    }
    for (int i = 2; i <= N; i++) {
      fact = (fact * i) % MOD;
    }
    long long sum_exc = (sum_div - fact + MOD) % MOD;
    printf("%lld %lld\n", sum_exc, fact);
  }
}
