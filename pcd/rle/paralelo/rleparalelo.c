#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_OUTPUT 1000000

void compress_rle_chunk(const char *input, int start, int end, char *output)
{
  int j = 0;
  for (int i = start; i < end; i++)
  {
    char current = input[i];
    int count = 1;
    while (i + 1 < end && input[i] == input[i + 1])
    {
      count++;
      i++;
    }
    j += sprintf(output + j, "%c%d", current, count);
  }
  output[j] = '\0';
}

int main()
{
  char input[] = "aaabbccccddddeeeeeff";
  int length = strlen(input);
  int numThreads = 4;

  char outputs[numThreads][MAX_OUTPUT];
  char finalOutput[MAX_OUTPUT];

  double start = omp_get_wtime();

#pragma omp parallel num_threads(numThreads)
  {
    int tid = omp_get_thread_num();
    int chunkSize = (length + numThreads - 1) / numThreads;
    int startIdx = tid * chunkSize;
    int endIdx = (tid + 1) * chunkSize;
    if (endIdx > length)
      endIdx = length;

    compress_rle_chunk(input, startIdx, endIdx, outputs[tid]);
  }

  // Junta os resultados na ordem dos threads
  finalOutput[0] = '\0';
  for (int t = 0; t < numThreads; t++)
  {
    strcat(finalOutput, outputs[t]);
  }

  double end = omp_get_wtime();

  printf("String comprimida: %s\n", finalOutput);
  printf("Tempo de execução (paralelo simples): %f segundos\n", end - start);

  return 0;
}
