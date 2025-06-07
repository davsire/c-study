#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

typedef struct Cliente {
  int sockfd;
  struct Cliente* prox;
} cliente_t;

typedef struct Pool {
  sem_t semaforo;
  pthread_mutex_t mutex;
  pthread_cond_t var_cond;
  cliente_t* inicio_fila;
  cliente_t* fim_fila;
} pool_t;


void inicializar_pool(pool_t* pool) {
  sem_init(&pool->semaforo, 0, NUM_THREADS);
  pthread_mutex_init(&pool-> mutex, NULL);
  pthread_cond_init(&pool->var_cond, NULL);
  pool->inicio_fila = NULL;
  pool->fim_fila = NULL;
}

void adicionar_cliente(pool_t* pool, int sockfd_client) {
  printf("Novo cliente sendo tratado\n");

  cliente_t* cliente = malloc(sizeof(cliente_t));
  cliente->sockfd = sockfd_client;
  cliente->prox = NULL;

  pthread_mutex_lock(&pool->mutex);
  if (pool->inicio_fila == NULL) {
    pool->inicio_fila = cliente;
    pool->fim_fila = cliente;
  } else {
    pool->fim_fila->prox = cliente;
    pool->fim_fila = cliente;
  }
  pthread_cond_broadcast(&pool->var_cond);
  pthread_mutex_unlock(&pool->mutex);
}

void* processar_cliente(void* args) {
  pool_t* pool = (pool_t *)args;
  cliente_t* cliente;
  char buffer[1];

  while (1) {
    pthread_mutex_lock(&pool->mutex);
    while (pool->inicio_fila == NULL) {
      pthread_cond_wait(&pool->var_cond, &pool->mutex);
    }
    cliente = pool->inicio_fila;
    pool->inicio_fila = cliente->prox;
    pthread_mutex_unlock(&pool->mutex);
  
    read(cliente->sockfd, &buffer, 1);
    printf("Número do cliente: %d\n", buffer[0]);
    buffer[0] *= 2;
    write(cliente->sockfd, &buffer, 1);
  
    close(cliente->sockfd);
    free(cliente);
    sem_post(&pool->semaforo);
  }
}

int main() {
  pthread_t threads[NUM_THREADS];
  pool_t pool;
  int sockfd_server, sockfd_client;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  inicializar_pool(&pool);
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, processar_cliente, (void *)&pool);
  }

  sockfd_server = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(1100);
  if (bind(sockfd_server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    printf("Erro ao inicilializar servidor...\n");
    exit(0);
  };
  listen(sockfd_server, 0);

  printf("Sevidor de pé!\n");
  while (1) {
    sem_wait(&pool.semaforo);
    sockfd_client = accept(sockfd_server, (struct sockaddr *)&client_addr, &client_addr_len);
    adicionar_cliente(&pool, sockfd_client);
  }
}
