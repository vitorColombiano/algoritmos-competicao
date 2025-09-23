#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int *L = (int*)malloc(n1 * sizeof(int));
  int *R = (int*)malloc(n2 * sizeof(int));

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];

  free(L);
  free(R);
}

void merge_sort(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main(void) {
  int N, Q, caso = 1;

  while (1) {
    scanf("%d %d", &N, &Q);
    if (N == 0 && Q == 0) break;

    int teste[N];
    int busca[Q];

    for (int i = 0; i < N; i++) {
      scanf("%d", &teste[i]);
    }
    for (int i = 0; i < Q; i++) {
      scanf("%d", &busca[i]);
    }

    merge_sort(teste, 0, N - 1);

    printf("CASE# %d:\n", caso++);
    for (int i = 0; i < Q; i++) {
      int encontrado = 0;
      for (int j = 0; j < N; j++) {
        if (busca[i] == teste[j]) {
          printf("%d found at %d\n", busca[i], j + 1);
          encontrado = 1;
          break;
        }
      }
      if (!encontrado) {
        printf("%d not found\n", busca[i]);
      }
    }
  }

  return 0;
}