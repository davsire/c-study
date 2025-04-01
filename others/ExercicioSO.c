#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void exe1() {
	fork();
	printf("Novo processo criado!\n");
}

void exe2() {
	int i;
	int pidPai = getpid();
	int pidFilho;

	for (i = 0; i < 4; i++) {
		pidFilho = fork();
		if (!pidFilho) {
			printf("Processo filho %d\n", getpid());
			break;
		}
		printf("Processo pai %d criou %d\n", pidPai, pidFilho);
	}
}

void exe3() {
	int i;
	int j;
	int pidFilhoA;
	int pidFilhoB;

	for (i = 0; i < 2; i++) {
		pidFilhoA = fork();
		if (!pidFilhoA) {
			printf("Processo %d filho de %d\n", getpid(), getppid());
			for (j = 0; j < 2; j++) {
				pidFilhoB = fork();
				if (!pidFilhoB) {
					printf("Processo %d filho de %d\n", getpid(), getppid());
					break;
				}
			}
			break;
		}
	}
}

int main() {
	exe3();
}
