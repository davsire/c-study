#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 128

int var_global = 0;
pthread_mutex_t mutex;

void* func_thread() {
	
	int j = 0;
	while (j < 100) {
		pthread_mutex_lock(&mutex);
		var_global++;
		pthread_mutex_unlock(&mutex);
		j++;
	}

	return NULL;
}

int main() {

	pthread_mutex_init(&mutex, NULL);	
	pthread_t threads[MAX_THREADS];

	int i;
	for (i = 0; i < MAX_THREADS; i++) {
		pthread_create(&(threads[i]), NULL, func_thread, NULL);
	}

	for (i = 0; i < MAX_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("Valor final: %d\n", var_global);

	return 0;
}

