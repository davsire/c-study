#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct No
{
	long int cod;
	char nome[256];
	unsigned int idade;
	char brasileiro; // 1: sim 0: nao
	double salario;
	struct No *prox;
} node_t;

node_t* criaNo(long int cod, char nome[], unsigned int idade, char brasileiro, double salario) {
	node_t *no = malloc(sizeof(node_t));
	no->cod = cod;
	strcpy(no->nome, nome);
	no->idade = idade;
	no->brasileiro = brasileiro;
	no->salario = salario;
	no-prox = NULL;
	return no;
}

node_t *cabeca = NULL;

node_t* insere(node_t *q) {
	if (cabeca == NULL) {
		cabeca = q;
		return q;
	}
	node_t *p = cabeca;
	while (p->prox != NULL) {
		p = p->prox;
	}
	p->prox = q;
	return q;
}

void retira(long int cod) {
	node_t *q, *p = cabeca;
	if (p->cod == cod) {
		cabeca = p->prox;
		free(p);
		return NULL;
	}
	while (p != NULL && p->cod != cod) {
		q = p;
		p = p->prox;
	}
	if (p != NULL) {
		q->prox = p->prox;
		free(p);
	}
}
