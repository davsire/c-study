#include <stdio.h>
#include <stdbool.h>

int main() {

	char s[10];
	
	if (false) {
		printf("Digite algo (scanf convencional):\n");
		scanf("%s", s);
		__fpurge(stdin);

		printf("Resultado: %s\n\n", s);

		printf("Digite algo (scanf formatado):\n");
		scanf("%9[^\n]s", s);
		__fpurge(stdin);

		printf("Resultado: %s\n\n", s);
	}

	if (true) {
		printf("Digite algo (leitura pelo gets):\n");
		gets(s);
		__fpurge(stdin);

		puts("Resultado:");
		puts(s);
		puts("");

		printf("Digite algo (leitura pelo fgets):\n");
		fgets(s, 10, stdin);
		__fpurge(stdin);

		puts("Resultado:");
		puts(s);
	}
}
