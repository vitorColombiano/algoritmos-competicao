#include <stdio.h>
#include <stdlib.h>

int merge(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int *L = (int*)malloc(n1 * sizeof(int));
  int *R = (int*)malloc(n2 * sizeof(int));

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  int inversao_count = 0;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
      inversao_count += (n1 - i);
    }
  }
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];

  free(L);
  free(R);
  return inversao_count;
}

int merge_sort(int arr[], int left, int right) {
  int inversao = 0;
  if (left < right) {
    int mid = left + (right - left) / 2;
    inversao += merge_sort(arr, left, mid);
    inversao += merge_sort(arr, mid + 1, right);
    inversao += merge(arr, left, mid, right);
  }
  return inversao;
}

int main(void) {
  int N, arr[100005];
  while (scanf("%d", &N) && N) {
    for (int i = 0; i < N; i++) {
      scanf("%d", &arr[i]);
    }
    int inversao = merge_sort(arr, 0, N - 1);
    if (inversao % 2 == 0) {
      printf("Carlos\n");
    } else {
      printf("Marcelo\n");
    }
  }
}
