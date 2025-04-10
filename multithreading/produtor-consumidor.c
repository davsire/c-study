#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t cheio;
sem_t vazio;

void* bob(void* args) {
	while (1) {
		sem_wait(&vazio);
		printf("Abastecendo a comida dos cachorros...\n");
		sleep((rand() % 4) + 1);
		printf("Abastecido!\n");
		sleep(1);
		sem_post(&cheio);
	}
}

void* alice(void* args) {
	while (1) {
		sem_wait(&cheio);
		printf("Cachorros comendo...\n");
		sleep((rand() % 4) + 1);
		printf("Comeram!\n");
		sleep(1);
		sem_post(&vazio);
	}
}

int main(int argc, char** argv) {
	sem_init(&cheio, 0, 0);
	sem_init(&vazio, 0, 1);
	srand(time(NULL));
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, bob, NULL);
	pthread_create(&threads[1], NULL, alice, NULL);

	int i;
	for (i = 0; i < 2; i++) {
		pthread_join(threads[i], NULL);
	}
}
