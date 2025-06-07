#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER (sizeof(uint8_t) * 2 + sizeof(int8_t) * 2)
#define NOME_ARQUIVO_SOCK "sock_fike"

#define SOMA 0
#define SUBTRACAO 1
#define MULTIPLICACAO 2
#define DIVISAO 3

typedef struct Mensagem {
  uint8_t cabecalho[2];
  int8_t dados[];
} mensagem_t;

void serializar_mensagem(char buffer[], mensagem_t* mensagem);

mensagem_t* desserializar_mensagem(char buffer[]);

#endif
