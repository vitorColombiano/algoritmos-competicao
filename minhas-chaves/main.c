#include <stdio.h>

int findInList(int key, int list[], int size) {
  for (int i = 0; i < size; i++) {
    if (list[i] == key) {
      return 0;
    }
  }
  list[size++] = key;
  return 1;
}

int main(void) {
  int Q, E;
  int keysE[1000];
  int keysQ[1000];

  scanf("%d %d", &Q, &E);
  for (int i = 0; i < E; i++) {
    scanf("%d", &keysE[i]);
  }

  for (int j = 0; j < Q; j++) {
    scanf("%d", &keysQ[j]);
  }

  for (int j = 0; j < Q; j++) {
    int find = findInList(keysQ[j], keysE, E++);
    printf("%d\n", find);
  }
  return 0;
}

