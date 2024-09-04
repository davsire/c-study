#include <stdio.h>

int main() {
	
	int dado = 10;
	printf("Dado inicial: %d\n", dado);
	
	dado++;
	printf("Dado pos incremento: %d\n", dado);
	
	dado--;
	printf("Dado pos decremento: %d\n", dado);
	
	dado += 3;
	printf("Dado acrescido de 3: %d\n", dado);
	
	dado -= 2;
	printf("Dado decrescido de 2: %d\n", dado);
	
	dado *= 10;
	printf("Dado pos multiplicar com 10: %d\n", dado);
		
	dado /= 2;
	printf("Dado pos dividir com 2: %d\n", dado);
}
