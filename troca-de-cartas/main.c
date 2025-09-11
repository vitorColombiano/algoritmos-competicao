#include <stdio.h>

static void sort(int v[], int n)
{
  for (int i = 1; i < n; i++)
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

int main(void) {
  int numCard1, numCard2;

  while (scanf("%d %d", &numCard1, &numCard2) == 2 && (numCard1 || numCard2)) {
    if (numCard1 == 0 && numCard2 == 0) break;

    int alice[10000], beatriz[10000];
    for(int i = 0; i < numCard1; i++) {
      scanf("%d", &alice[i]);
    }
    for(int i = 0; i < numCard2; i++) {
      scanf("%d", &beatriz[i]);
    }

    sort(alice, numCard1);
    sort(beatriz, numCard2);

    // Contar cartas únicas de Alice que Beatriz não tem
    int i = 0, j = 0, unicasAlice = 0;
    for (; i < numCard1 && j < numCard2; ) {
      if (alice[i] < beatriz[j]) {
        unicasAlice++;
        // Pular cartas repetidas de Alice
        int atual = alice[i];
        for (; i < numCard1 && alice[i] == atual; i++);
      } else if (alice[i] > beatriz[j]) {
        j++;
      } else {
        // Cartas iguais - pular ambas
        int atual = alice[i];
        for (; i < numCard1 && alice[i] == atual; i++);
        for (; j < numCard2 && beatriz[j] == atual; j++);
      }
    }
    // Cartas restantes de Alice
    for (; i < numCard1; ) {
      unicasAlice++;
      int atual = alice[i];
      for (; i < numCard1 && alice[i] == atual; i++);
    }

    // Contar cartas únicas de Beatriz que Alice não tem
    i = 0; j = 0;
    int unicasBeatriz = 0;
    for (; i < numCard1 && j < numCard2; ) {
      if (beatriz[j] < alice[i]) {
        unicasBeatriz++;
        // Pular cartas repetidas de Beatriz
        int atual = beatriz[j];
        for (; j < numCard2 && beatriz[j] == atual; j++);
      } else if (beatriz[j] > alice[i]) {
        i++;
      } else {
        // Cartas iguais - pular ambas
        int atual = beatriz[j];
        for (; i < numCard1 && alice[i] == atual; i++);
        for (; j < numCard2 && beatriz[j] == atual; j++);
      }
    }
    // Cartas restantes de Beatriz
    for (; j < numCard2; ) {
      unicasBeatriz++;
      int atual = beatriz[j];
      for (; j < numCard2 && beatriz[j] == atual; j++);
    }

    // O máximo de trocas é o menor dos dois
    int maxTrocas = unicasAlice < unicasBeatriz ? unicasAlice : unicasBeatriz;
    printf("%d\n", maxTrocas);
  }
  return 0;
}