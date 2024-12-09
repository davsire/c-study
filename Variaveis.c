#include <stdio.h>

// constante
#define texto "Entrada e saida de dados."

int main() {
	
	printf("%s\n", texto);
	
	int idade = 0;
	float altura = 0.0;
	char nome[50] = "";
	
	printf("Digite sua idade:\n");
	scanf("%d", &idade);
	
	printf("Digite sua altura:\n");
	scanf("%f", &altura);
	
	printf("Digite seu nome:\n");
	scanf("%s", nome);
	
	printf("Idade: %d, Altura: %.2f, Nome: %s\n", idade, altura, nome);
}
