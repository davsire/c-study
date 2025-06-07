#include "protocolo.h"

void serializar_mensagem(char buffer[], mensagem_t* mensagem) {
  memcpy(buffer, mensagem->cabecalho, 2);
  memcpy(buffer + 2, mensagem->dados, mensagem->cabecalho[1]);
}

mensagem_t* desserializar_mensagem(char buffer[]) {
  mensagem_t* mensagem = malloc(sizeof(MAX_BUFFER));
  memcpy(mensagem->cabecalho, buffer, 2);
  memcpy(mensagem->dados, buffer + 2, mensagem->cabecalho[1]);
  return mensagem;
}
