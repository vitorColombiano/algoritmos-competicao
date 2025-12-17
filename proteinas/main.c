#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005

int N, M;
char DNA[MAXN], PROT[MAXN];

int sa[MAXN], tmpSA[MAXN];
int rnk[MAXN], tmpRnk[MAXN];
int cnt[MAXN], Nmax;

void build_sa(char *s, int n) {
  Nmax = (n > 256 ? n : 256);

  for (int i = 0; i < n; i++) {
    sa[i] = i;
    rnk[i] = s[i];
  }

  for (int k = 1; ; k <<= 1) {
    memset(cnt, 0, sizeof(int) * Nmax);

    for (int i = 0; i < n; i++) {
      int idx = (i + k < n ? rnk[i + k] : 0);
      cnt[idx]++;
    }
    for (int i = 1; i < Nmax; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) {
      int idx = (sa[i] + k < n ? rnk[sa[i] + k] : 0);
      tmpSA[--cnt[idx]] = sa[i];
    }

    memset(cnt, 0, sizeof(int) * Nmax);
    for (int i = 0; i < n; i++) cnt[rnk[i]]++;
    for (int i = 1; i < Nmax; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--)
      sa[--cnt[rnk[tmpSA[i]]]] = tmpSA[i];

    tmpRnk[sa[0]] = 1;
    for (int i = 1; i < n; i++) {
      int a = sa[i - 1], b = sa[i];
      tmpRnk[b] = tmpRnk[a] +
        (rnk[a] != rnk[b] ||
         (a + k < n ? rnk[a + k] : 0) != (b + k < n ? rnk[b + k] : 0));
    }
    for (int i = 0; i < n; i++) rnk[i] = tmpRnk[i];

    if (rnk[sa[n - 1]] == n) break;
  }
}

int lcp[MAXN];

void build_lcp(char *s, int n) {
  int k = 0;
  static int inv[MAXN];

  for (int i = 0; i < n; i++) inv[sa[i]] = i;

  for (int i = 0; i < n; i++) {
    if (inv[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = sa[inv[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    lcp[inv[i]] = k;
    if (k) k--;
  }
}

int st[20][MAXN];
int lg[MAXN];

void build_rmq(int n) {
  for (int i = 0; i < n; i++)
    st[0][i] = lcp[i];

  for (int i = 2; i <= n; i++)
    lg[i] = lg[i / 2] + 1;

  for (int k = 1; (1 << k) <= n; k++) {
    for (int i = 0; i + (1 << k) <= n; i++) {
      int x = st[k - 1][i];
      int y = st[k - 1][i + (1 << (k - 1))];
      st[k][i] = (x < y ? x : y);
    }
  }
}

int rmq(int l, int r) {
  if (l > r) { int tmp = l; l = r; r = tmp; }
  int len = r - l + 1;
  int k = lg[len];
  int x = st[k][l];
  int y = st[k][r - (1 << k) + 1];
  return (x < y ? x : y);
}

int lcp_with_suffix(int pos, int idx) {
  int saPos = sa[idx];
  if (pos == saPos) return N - pos;

  int a = saPos;
  int b = pos;

  int ra = 0, rb = 0;
  for (int i = 0; i < N; i++) {
    if (sa[i] == a) { ra = i; break; }
  }
  rb = -1;

  // achar rb
  for (int i = 0; i < N; i++) {
    if (sa[i] == b) { rb = i; break; }
  }
  if (rb == -1) return 0;

  if (ra == rb) return N - a;

  return rmq(ra, rb - 1);
}

int cmp_pattern_suffix(int idx, int A, int B) {
  int pos = sa[idx];
  int L = B - A + 1;

  int l = 0;
  while (pos + l < N && A + l < M && DNA[pos + l] == PROT[A + l])
    l++;

  if (l == L) return 0;
  if (pos + l == N) return -1;

  return (DNA[pos + l] < PROT[A + l]) ? -1 : 1;
}

int lower_bound_sa(int A, int B) {
  int l = 0, r = N;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (cmp_pattern_suffix(mid, A, B) < 0)
      l = mid + 1;
    else
      r = mid;
  }
  return l;
}

int upper_bound_sa(int A, int B) {
  int l = 0, r = N;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (cmp_pattern_suffix(mid, A, B) <= 0)
      l = mid + 1;
    else
      r = mid;
  }
  return l;
}

int main() {
  scanf("%d %d", &N, &M);
  scanf("%s", DNA);
  scanf("%s", PROT);

  build_sa(DNA, N);
  build_lcp(DNA, N);
  build_rmq(N);

  int Q;
  scanf("%d", &Q);

  while (Q--) {
    int A, B;
    scanf("%d %d", &A, &B);
    A--; B--;

    int L = lower_bound_sa(A, B);
    int R = upper_bound_sa(A, B);

    printf("%d\n", R - L);
  }
  return 0;
}
