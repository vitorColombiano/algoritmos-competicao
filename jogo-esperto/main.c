#include <stdio.h>
#include <string.h>

#define MAXLIM 200005

typedef struct {
  int val, steps;
} Node;

char visited[MAXLIM];

int bfs(int N, int M)
{
  int limit = 2 * (N > M ? N : M) + 50;
  if (limit >= MAXLIM)
    limit = MAXLIM - 1;

  Node queue[MAXLIM];
  int front = 0, rear = 0;

  memset(visited, 0, (limit + 1) * sizeof(char));

  if (N < 0 || N > limit || M < 0 || M > limit)
    return -1;

  queue[rear++] = (Node){N, 0};
  visited[N] = 1;

  while (front < rear)
  {
    Node curr = queue[front++];

    if (curr.val == M)
      return curr.steps;

    int next_vals[6] = {
        curr.val * 2,
        curr.val * 3,
        curr.val / 2,
        curr.val / 3,
        curr.val + 7,
        curr.val - 7};

    for (int i = 0; i < 6; i++)
    {
      int next = next_vals[i];

      if ((i == 2 && curr.val % 2 != 0) || (i == 3 && curr.val % 3 != 0))
        continue;

      if (next < 0 || next > limit)
        continue;

      if (!visited[next])
      {
        visited[next] = 1;
        queue[rear++] = (Node){next, curr.steps + 1};
      }
    }
  }

  return -1;
}

int main(void)
{
  int N, M;
  if (scanf("%d %d", &N, &M) != 2)
    return 1;
  printf("%d\n", bfs(N, M));
  return 0;
}
