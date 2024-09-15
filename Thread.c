#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function() {
	printf("thread_function executando.\n");
	pthread_exit("Obrigado pelo tempo de CPU!");
}

int main() {
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	res = pthread_join(a_thread, &thread_result);
	printf("Thread joined, retornou: %s\n", (char *)thread_result);
	printf("Fim da exec\n");
	exit(0);
}
