#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

pthread_rwlock_t sem;
int data = 0;

void* leitor(void* args) {
	int tid = *((int *)args);
	while (1) {
		sleep(rand() % 4);
		pthread_rwlock_rdlock(&sem);
		printf("Thread %d leu dado: %d\n", tid, data);
		pthread_rwlock_unlock(&sem);
	}
}

void* escritor(void* args) {
	int tid = *((int *)args);
	while (1) {
		sleep(rand() % 4);
		pthread_rwlock_wrlock(&sem);
		data++;
		printf("Thread %d escreveu dado: %d\n", tid, data);
		pthread_rwlock_unlock(&sem);
	}
}

int main(int argc, char** argv) {
	pthread_rwlock_init(&sem, NULL);
	srand(time(NULL));

	if (argc < 3) {
		printf("Informe: numThreads numEscritores\n");
		exit(0);
	}

	int num_threads = atoi(argv[1]);
	int num_escritores = atoi(argv[2]);

	if (num_threads <= num_escritores) {
		printf("O número de escritores deve ser menor que o número total de threads!\n");
		exit(0);
	}

	pthread_t threads[num_threads];
	int qtd_escritores = 0;
	int i;

	for (i = 0; i < num_threads; i++) {
		if ((rand() % 2) || qtd_escritores == num_escritores) {
			pthread_create(&threads[i], NULL, leitor, &i);
		} else {
			pthread_create(&threads[i], NULL, escritor, &i);
			qtd_escritores++;
		}
	}

	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
}
