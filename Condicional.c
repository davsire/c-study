#include <stdio.h>
#include <stdbool.h>

int main() {
	// IF
	if (false) {
		float m;
		
		printf("Insira sua nota:\n");
		scanf("%f", &m);
		
		if (m >= 7.0) {
			printf("Aprovado(a)!\n");
		} else {
			printf("Reprovado(a)!\n");
		}
	}
	
	// SWITCH
	if (true) {
		int d;
		
		printf("Insira um numero de 1 a 7:\n");
		scanf("%d", &d);
		
		switch (d) {
			case 1:
				printf("Domingo");
				break;
			case 2:
				printf("Segunda");
				break;
			case 3:
				printf("Terca");
				break;
			case 4:
				printf("Quarta");
				break;
			case 5:
				printf("Quinta");
				break;
			case 6:
				printf("Sexta");
				break;
			case 7:
				printf("Sabado");
				break;
			default:
				printf("Numero invalido!");
		}
	}

}
