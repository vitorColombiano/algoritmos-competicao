#include <stdio.h>
#include <omp.h>
#include <time.h>
#define N 1000000000

int main(int argc, char *argv[]){
  double x, final;
  int i;
  clock_t start, end;
  double time;
  int num_threads = 4;

  final = 1;
  x = 1 + 1.0/N;

  start = clock();
  omp_set_num_threads(num_threads);
#pragma omp parallel default(none) private(i) shared(x) reduction(*:final)
  {
#pragma omp for
    for(i=0; i<N; i++) {
      final = final*x;
    }
  }
  
  end = clock();
  time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Resultado=%lf\n",final);
  printf("Tempo=%lf\n",time);
  return 0;
}