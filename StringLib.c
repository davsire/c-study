#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define N 20
#define M 50

int main() {
	setlocale(LC_ALL, "Portuguese");

	// strcpy
	if (false) {
		char origem[N] = {"Olá, mundo!"};
		char destino[N];

		printf("Antes do strcpy:\n");
		puts(origem);
		puts(destino);

		strcpy(destino, origem);

		printf("Depois do strcpy:\n");
		puts(origem);
		puts(destino);
	}

	// strcat
	if (false) {
		char s1[M] = {"Lógica de"};
		char s2[M] = {" Programação"};

		printf("Antes do strcat:\n");
		printf("str1: %s\n", s1);
		printf("str2: %s\n", s2);

		strcat(s1, s2);

		printf("Depois do strcat:\n");
		printf("str1: %s\n", s1);
		printf("str2: %s\n", s2);
	}

	// strlen
	if (false) {
		char s[M];
		int i;

		printf("Digite um texto:\n");
		gets(s);
		i = strlen(s);
		printf("\nTamaho do texto: %d\n\n", i);

		printf("Impressão de posição a posição:\n");
		for (i = 0; i < strlen(s); i++) {
			printf("%c", s[i]);
		}
	}

	// strcmp
	if (true) {
		char hardText[M] = {"/exit"};
		char senhaUsr[M];
		int ok;

		printf("Digite um texto:\n");
		gets(senhaUsr);

		ok = !strcmp(hardText, senhaUsr);

		if (ok) puts("Textos iguais");
		else puts("Textos diferentes");
	}
}
