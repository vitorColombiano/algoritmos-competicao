#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXP 8
#define MAXQ 2000000
#define VISMAX 200003

typedef struct {
  int knight;
  int npawns;
  int pawns[MAXP];
  int dist;
} State;

// movimentos do cavalo (dr, dc)
int KM[8][2] = {
  {2,1}, {1,2}, {-1,2}, {-2,1},
  {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
};

// converte posição (1..64) -> (linha, coluna) 0-index
void pos_to_rc(int p, int *r, int *c) {
  p--;
  *r = p / 8;
  *c = p % 8;
}

int rc_to_pos(int r, int c) {
  return r * 8 + c + 1;
}

// gera todos os movimentos válidos do cavalo a partir de p
int knight_moves_from(int p, int *out) {
  int r, c;
  pos_to_rc(p, &r, &c);
  int k = 0;
  for (int i = 0; i < 8; i++) {
    int nr = r + KM[i][0];
    int nc = c + KM[i][1];
    if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8)
      out[k++] = rc_to_pos(nr, nc);
  }
  return k;
}

// ordenação simples (suficiente para ≤ 8 elementos)
void sort(int *a, int n) {
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (a[j] < a[i]) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
      }
}

// compara dois estados
int equal_state(State *a, State *b) {
  if (a->knight != b->knight || a->npawns != b->npawns) return 0;
  for (int i = 0; i < a->npawns; i++)
    if (a->pawns[i] != b->pawns[i]) return 0;
  return 1;
}

// hashing simples (baseado em knight + posições dos peões)
State visited[VISMAX];
int vis_used[VISMAX];

int hash_state(State *s) {
  long long h = s->knight;
  for (int i = 0; i < s->npawns; i++) h = h * 131LL + s->pawns[i];
  if (h < 0) h = -h;
  return (int)(h % VISMAX);
}

int was_visited(State *s) {
  int h = hash_state(s);
  int start = h;
  while (vis_used[h]) {
    if (equal_state(&visited[h], s)) return 1;
    h = (h + 1) % VISMAX;
    if (h == start) break;
  }
  return 0;
}

void mark_visited(State *s) {
  int h = hash_state(s);
  while (vis_used[h]) h = (h + 1) % VISMAX;
  vis_used[h] = 1;
  visited[h] = *s;
}

// BFS principal: retorna número mínimo de movimentos ou -1 se impossível
int solve_instance(int np, int *pawns, int knight) {
  State start;
  start.knight = knight;
  start.npawns = np;
  for (int i = 0; i < np; i++) start.pawns[i] = pawns[i];
  sort(start.pawns, start.npawns);
  start.dist = 0;

  static State queue[MAXQ];
  int qh = 0, qt = 0;
  queue[qt++] = start;

  memset(vis_used, 0, sizeof(vis_used));
  mark_visited(&start);

  const int last_row_start = 57, last_row_end = 64;

  while (qh < qt) {
    State cur = queue[qh++];

    // se não há peões -> venceu
    if (cur.npawns == 0) return cur.dist;

    // quantos "reis" (peões já na última linha) existem no estado atual?
    int kings_now = 0, kingpos = -1;
    for (int i = 0; i < cur.npawns; i++)
      if (cur.pawns[i] >= last_row_start && cur.pawns[i] <= last_row_end) {
        kings_now++;
        kingpos = cur.pawns[i];
      }
    if (kings_now >= 2) continue; // ramo inválido: cavalo só tem uma jogada

    int moves[8];
    int nm = knight_moves_from(cur.knight, moves);

    // se há exatamente um rei agora, o cavalo deve capturá-lo nesta jogada
    if (kings_now == 1) {
      int can = 0;
      for (int i = 0; i < nm; i++) if (moves[i] == kingpos) { can = 1; break; }
      if (!can) continue;
      moves[0] = kingpos;
      nm = 1;
    }

    for (int i = 0; i < nm; i++) {
      int nxt = moves[i];
      int newp[MAXP], newn = 0;

      // captura se aterrissar numa casa com peão
      for (int j = 0; j < cur.npawns; j++)
        if (cur.pawns[j] != nxt) newp[newn++] = cur.pawns[j];

      // checa se algum peão captura o cavalo no avanço seguinte (p+8 == nxt)
      int dead = 0;
      for (int j = 0; j < newn; j++)
        if (newp[j] + 8 == nxt) { dead = 1; break; }
      if (dead) continue;

      // avança peões (+8)
      for (int j = 0; j < newn; j++) newp[j] += 8;

      // se dois ou mais se tornam reis -> ramo inválido
      int kings_after = 0;
      for (int j = 0; j < newn; j++)
        if (newp[j] >= last_row_start && newp[j] <= last_row_end) kings_after++;
      if (kings_after >= 2) continue;

      State ns;
      ns.knight = nxt;
      ns.npawns = newn;
      ns.dist = cur.dist + 1;
      for (int j = 0; j < newn; j++) ns.pawns[j] = newp[j];
      sort(ns.pawns, ns.npawns);

      if (!was_visited(&ns)) {
        mark_visited(&ns);
        if (qt < MAXQ) queue[qt++] = ns;
      }
    }
  }

  return -1;
}

int main() {
  int P;
  while (scanf("%d", &P) == 1) {
    if (P == 0) break;
    int pawns[MAXP];
    for (int i = 0; i < P; i++) scanf("%d", &pawns[i]);
    int H; scanf("%d", &H);
    int ans = solve_instance(P, pawns, H);
    if (ans == -1) printf("impossible\n");
    else printf("%d\n", ans);
  }
  return 0;
}
