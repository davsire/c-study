#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

struct timeval t1, t2;
int found = 0;

// djb2 hash (referencia: http://www.cse.yorku.ca/~oz/hash.html)
unsigned long hash_djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

// Converte a hash para string com representacao hexadecimal (para legibilide)
void htos(unsigned long hash, char output[65]) {
    sprintf(output, "%lx", hash);
}

// Verifica se a hash termina com num_zeros numeros zeros
int check_hash_zeros(char *hash_str, int num_zeros) {
    int len = strlen(hash_str);
    for (int i = len - num_zeros; i < len; i++) {
        if (hash_str[i] != '0') {
            return 0;
        }
    }
    return 1;
}

void PoW(char *data, int num_zeros, int n, int acc) {
    unsigned long hash;
    char hash_str[65];
    long long nonce = n;
    char buffer[256];
    
    // Minerador alterar o valor de nonce ate encontrar a hash que satisfaca o desafio
    while (!found) {
        // Concatena o dado do bloco com o nonce
        sprintf(buffer, "%s%lld", data, nonce);
        
        // computa a hash do string concatenado (bloco + nonce)
        hash = hash_djb2((unsigned char *)buffer);
        
        // Para visualizar a hash em formato hexadecimal
        htos(hash, hash_str);
        
        if (check_hash_zeros(hash_str, num_zeros)) {
            printf("Sucesso! Valor do nonce: %lld\n", nonce);
            printf("Hash: %s\n", hash_str);
            found = 1;
            break;
        }
        nonce += acc;
    }
}

int main(int argc, char **argv) {
    char data[] = "Exemplo de dados do bloco";  // Representa o conteudo do bloco
    int num_zeros;       // Numero de zeros requeridos no final do hash
    int num_threads;
    int i;

    if(argc < 2){
	    printf("Digite %s num_zeros\n", argv[0]);
	    exit(0);
    }
    
    if (argc < 3) {
	    printf("Digite %s num_threads\n", argv[0]);
	    exit(0);
    }

    num_zeros = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    gettimeofday(&t1, NULL);
    
    printf("Executando PoW ...\n");
    #pragma omp parallel for
    for (i = 0; i < num_threads; i++) {
        PoW(data, num_zeros, i, num_threads);
    }

    gettimeofday(&t2, NULL);

    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Tempo total: %f\n", t_total);

    return 0;
}
