#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//#define IMPRIME

#define MAX_NUMBERS 500000000
//#define MAX_NUMBERS 10
#define MAX_VALUE 1000;

float numbers[MAX_NUMBERS];
unsigned int i;
struct timeval t1, t2;

int init_numbers(){
  unsigned int seed;
  for(i = 0; i < MAX_NUMBERS; i++)
    numbers[i] = ((float)rand_r(&seed)/(float)RAND_MAX) * MAX_VALUE;
  return 0;
}

int show_numbers(){
  for (i = 0; i < MAX_NUMBERS; i++)
    printf("number[%u] = %f\n",i,numbers[i]);
  return 0;
}

int main (int argc, char **argv){ 
  init_numbers();

  #ifdef IMPRIME
    show_numbers();
  #endif

  gettimeofday(&t1, NULL);
  for (i = 0; i < MAX_NUMBERS; i++){
    numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;    
  }
  gettimeofday(&t2, NULL);

  #ifdef IMPRIME
    printf("Apos a operacao matematica\n"); 
    show_numbers();
  #endif

  double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
  printf("Tempo total: %f\n", t_total);

  return 0;
}