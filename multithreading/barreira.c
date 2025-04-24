#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
  int limite;
  int contador;
  pthread_mutex_t mtx;
  pthread_cond_t cond;
} barreira_t;

void inicializa_barreira(barreira_t* barreira, int count) {
  barreira->limite = count;
  barreira->contador = 0;
  pthread_mutex_init(&barreira->mtx, NULL);
  pthread_cond_init(&barreira->cond, NULL);
}

void espera(barreira_t* barreira) {
  pthread_mutex_lock(&barreira->mtx);
  barreira->contador++;
  if (barreira->contador == barreira->limite) {
    pthread_cond_broadcast(&barreira->cond);
  } else {
    pthread_cond_wait(&barreira->cond, &barreira->mtx);
  }
  pthread_mutex_unlock(&barreira->mtx);
}

void* print_alo(void* arg) {
  barreira_t* barreira = (barreira_t*)arg;
  sleep(4);
  printf("Alo\n");
  espera(barreira);
}

void* print_mundo(void* arg) {
  barreira_t* barreira = (barreira_t*)arg;
  espera(barreira);
  printf("Mundo!\n");
}

int main() {
  barreira_t barreira;
  pthread_t th_alo, th_mundo1, th_mundo2, th_mundo3;

  inicializa_barreira(&barreira, 4);

  pthread_create(&th_alo, NULL, print_alo, (void*)&barreira);
  pthread_create(&th_mundo1, NULL, print_mundo, (void*)&barreira);
  pthread_create(&th_mundo2, NULL, print_mundo, (void*)&barreira);
  pthread_create(&th_mundo3, NULL, print_mundo, (void*)&barreira);

  pthread_join(th_alo, NULL);
  pthread_join(th_mundo1, NULL);
  pthread_join(th_mundo2, NULL);
  pthread_join(th_mundo3, NULL);

  return 0;
}
