#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define NUM_MAXIMO 100

typedef struct {
  int num_escolhido;
  int num_sorte;

  int id_ultimo_acerto;
  int pos_ultimo_acerto;
  int num_tentativas_ultimo_acerto;

  pthread_mutex_t mtx;
  pthread_cond_t cond_inicio;
  pthread_cond_t cond_acerto;
} sorteio_t;

typedef struct {
  int id;
  sorteio_t* sorteio;
} apostador_t;

void inicializar_sorteio(sorteio_t* sorteio) {
  sorteio->num_escolhido = FALSE;
  sorteio->pos_ultimo_acerto = 0;
  pthread_mutex_init(&sorteio->mtx, NULL);
  pthread_cond_init(&sorteio->cond_inicio, NULL);
  pthread_cond_init(&sorteio->cond_acerto, NULL);
}

void terminar_sorteio(sorteio_t* sorteio) {
  pthread_mutex_destroy(&sorteio->mtx);
  pthread_cond_destroy(&sorteio->cond_inicio);
  pthread_cond_destroy(&sorteio->cond_acerto);
}

void* auditor(void* args) {
  sorteio_t* sorteio = (sorteio_t *)args;

  sleep(2);
  pthread_mutex_lock(&sorteio->mtx);
  int num_sorte = rand() % NUM_MAXIMO;
  sorteio->num_sorte = num_sorte;
  sorteio->num_escolhido = TRUE;
  printf("Número da sorte escolhido! (%d)\n", num_sorte);
  pthread_cond_broadcast(&sorteio->cond_inicio);
  pthread_mutex_unlock(&sorteio->mtx);

  while (TRUE) {
    pthread_mutex_lock(&sorteio->mtx);
    pthread_cond_wait(&sorteio->cond_acerto, &sorteio->mtx);
    printf(
      "Thread %d acertou o número da sorte com %d tentativas! (%d° posição)\n",
      sorteio->id_ultimo_acerto, sorteio->num_tentativas_ultimo_acerto, sorteio->pos_ultimo_acerto
    );
    pthread_mutex_unlock(&sorteio->mtx);
  }
}

void* apostador(void* args) {
  apostador_t* apostador_arg = (apostador_t *)args;
  sorteio_t* sorteio = apostador_arg->sorteio;
  int num_tentativas = 0;
  int numero;

  pthread_mutex_lock(&sorteio->mtx);
  while (!sorteio->num_escolhido) {
    pthread_cond_wait(&sorteio->cond_inicio, &sorteio->mtx);
  }
  pthread_mutex_unlock(&sorteio->mtx);

  printf("Thread %d iniciando chutes do número da sorte...\n", apostador_arg->id);
  while (TRUE) {
    usleep(1000);
    num_tentativas++;
    numero = rand() % NUM_MAXIMO;
    if (numero == sorteio->num_sorte) {
      pthread_mutex_lock(&sorteio->mtx);
      sorteio->id_ultimo_acerto = apostador_arg->id;
      sorteio->pos_ultimo_acerto++;
      sorteio->num_tentativas_ultimo_acerto = num_tentativas;
      pthread_cond_signal(&sorteio->cond_acerto);
      pthread_mutex_unlock(&sorteio->mtx);
      free(apostador_arg);
      break;
    }
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Informe o número de apostadores!\n");
    exit(1);
  }

  srand(time(NULL));
  int i;
  int num_apostadores = atoi(argv[1]);
  sorteio_t sorteio;
  pthread_t th_auditora;
  pthread_t th_apostadoras[num_apostadores];

  inicializar_sorteio(&sorteio);

  pthread_create(&th_auditora, NULL, auditor, (void *)&sorteio);
  for (i = 0; i < num_apostadores; i++) {
    apostador_t* arg_apostador = malloc(sizeof(apostador_t));
    arg_apostador->id = i + 1;
    arg_apostador->sorteio = &sorteio;
    pthread_create(&th_apostadoras[i], NULL, apostador, (void *)arg_apostador);
  }

  for (i = 0; i < num_apostadores; i++) {
    pthread_join(th_apostadoras[i], NULL);
  }
  pthread_cancel(th_auditora);

  terminar_sorteio(&sorteio);

  exit(0);
}
