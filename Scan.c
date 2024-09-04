#include <stdio.h>

int main() {
	
	int idade = 0;
	float peso = 0.0;

	printf("Informe sua idade e ano:\n");
	scanf("%d", &idade);
	
	printf("Informe seu peso:\n");
	scanf("%f", &peso);
	
	printf("Idade informada: %d\n", idade);
	printf("Peso informado: %.1f\n", peso);
}
