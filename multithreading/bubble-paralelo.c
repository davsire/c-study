#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

// #define IMPRIME

typedef struct args {
  int size;
  int *array;
} bubble_args_t;

void imprime(int **array, int num_arrays, int size) {
  int i,j;
  for(i=0; i < num_arrays; i++){
	 for(j=0; j < size; j++){
		printf("%d ", array[i][j]);
	 }
	 printf("\n");
  }
}

void *bubble(void *args) {
  bubble_args_t *bubble_args = (bubble_args_t *)args;
  int i,j;
  int temp;
  for(i = 0; i < bubble_args->size-1; i++){       
    for(j = 0; j < bubble_args->size-i-1; j++){          
      if(bubble_args->array[j] > bubble_args->array[j+1]){               
        temp = bubble_args->array[j];
        bubble_args->array[j] = bubble_args->array[j+1];
        bubble_args->array[j+1] = temp;
      }
    }
  }
}

int main(int argc, char **argv){
  int **elementos, n, tam, i, j;
  struct timeval t1, t2;
  double t_total;

  if (argc != 3) {
    printf("Digite %s Num_arrays Num_elementos\n", argv[0]);
    exit(0);
  }
  n = atoi(argv[1]);
  tam = atoi(argv[2]);
  pthread_t threads[n];

  srand(time(NULL));

  elementos=(int**)malloc(n*sizeof(int*));
  for(i = 0; i < n; i++) {
    elementos[i]=(int*)malloc(tam*sizeof(int));
  }

  for(i = 0; i < n; i++) {
    for (j = 0; j < tam; j++) {
      elementos[i][j] = rand() % 1000;
    }
  }

  #ifdef IMPRIME
    printf("Antes da ordenacao!\n");
    imprime(elementos, n, tam);
    printf("\n");
  #endif

  gettimeofday(&t1, NULL);
  for (i = 0; i < n; i++) {
    bubble_args_t *args = malloc(sizeof(bubble_args_t));
    args->size = tam;
    args->array = elementos[i];
    pthread_create(&threads[i], NULL, bubble, (void *)args);
  }
  for (i = 0; i < n; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&t2, NULL);

  t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec)/1000000.0);
 
  #ifdef IMPRIME
    printf("Apos a ordenacao!\n");
    imprime(elementos, n, tam);
    printf("\n");
  #endif

  for(i=0;i<n;i++){
		free(elementos[i]);
	}
	free(elementos);

  printf("Tempo total = %f\n", t_total);

  return 0;
}
