#include <stdio.h>
#include <stdlib.h>

int main()
{
  int N, B;
  while (1)
  {
    scanf("%d %d", &N, &B);
    if (N == 0 && B == 0)
      break;

    int bolas[100];
    int possible[100];

    for (int i = 0; i < B; i++)
    {
      scanf("%d", &bolas[i]);
    }

    // inicializa vetor de possibilidades com 0
    for (int i = 0; i <= N; i++)
    {
      possible[i] = 0;
    }

    // calcula todas as diferenças
    for (int i = 0; i < B; i++)
    {
      for (int j = 0; j < B; j++)
      {
        int diff = abs(bolas[i] - bolas[j]);
        if (diff <= N)
        {
          possible[diff] = 1;
        }
      }
    }

    int ok = 1;
    for (int i = 0; i <= N; i++)
    {
      if (!possible[i])
      {
        ok = 0;
        break;
      }
    }

    if (ok)
      printf("Y\n");
    else
      printf("N\n");
  }
  return 0;
}
