#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

struct timeval t1, t2;

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Informe o tamanho N das matrizes quadradas!\n");
    return 1;
  }

  int N = atoi(argv[1]);

  int A[N][N], B[N][N], C[N][N];

  gettimeofday(&t1, NULL);
  
  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
      C[i][j] = 0;
    }
  }

  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  gettimeofday(&t2, NULL);

  double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0); 
  printf("Tempo total: %f\n", t_total);

  return 0;
}
