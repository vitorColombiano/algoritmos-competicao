#include <stdio.h>

static void sort3(int v[3])
{
  for (int i = 1; i < 3; i++)
  {
    int x = v[i], j = i - 1;
    while (j >= 0 && v[j] > x)
    {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = x;
  }
}

static int princess_wins(const int a[3], const int b[3])
{
  int i = 0, j = 0, wins = 0;
  while (i < 3 && j < 3)
  {
    if (a[i] > b[j])
    {
      wins++;
      i++;
      j++;
    }
    else
    {
      i++;
    }
  }
  return wins;
}

int main(void)
{
  int A, B, C, X, Y;
  while (scanf("%d %d %d %d %d", &A, &B, &C, &X, &Y) == 5)
  {
    if (A == 0 && B == 0 && C == 0 && X == 0 && Y == 0)
      break;

    int used[53] = {0};
    used[A] = used[B] = used[C] = used[X] = used[Y] = 1;

    int princess[3] = {A, B, C};
    sort3(princess);

    int answer = -1;

    for (int cand = 1; cand <= 52; cand++)
    {
      if (used[cand])
        continue;

      int prince[3] = {X, Y, cand};
      sort3(prince);

      int pw = princess_wins(princess, prince);
      if (pw <= 1)
      {
        answer = cand;
        break;
      }
    }

    printf("%d\n", answer);
  }
  return 0;
}
