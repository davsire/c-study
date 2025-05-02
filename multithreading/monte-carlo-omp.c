#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

struct timeval t1, t2;

int main() {
  long long num_trials = 1000000000;
  long long count = 0;

  gettimeofday(&t1, NULL);

  #pragma omp parallel
  {
    unsigned int seed = 1234 + omp_get_thread_num();
    #pragma omp for reduction(+:count)
    for (long long i = 0; i < num_trials; i++) {
      double x = (double)rand_r(&seed) / RAND_MAX;
      double y = (double)rand_r(&seed) / RAND_MAX;
      if (x * x + y * y <= 1.0) {
        count++;
      }
    }
  }

  gettimeofday(&t2, NULL);

  double pi_estimate = 4.0 * count / num_trials;
  printf("Valor de Pi: %f\n", pi_estimate);

  double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
  printf("Tempo total: %f\n", t_total);

  return 0;
}
