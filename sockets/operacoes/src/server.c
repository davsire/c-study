#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "protocolo/protocolo.h"

int operar(uint8_t operador, int8_t operandos[]) {
  switch (operador) {
    case SOMA:
      return operandos[0] + operandos[1];
    case SUBTRACAO:
      return operandos[0] - operandos[1];
    case MULTIPLICACAO:
      return operandos[0] * operandos[1];
    case DIVISAO:
      return operandos[0] / operandos[1];
  }
}

char obter_operador(uint8_t operador) {
  switch (operador) {
    case SOMA:
      return '+';
    case SUBTRACAO:
      return '-';
    case MULTIPLICACAO:
      return '*';
    case DIVISAO:
      return '/';
  }
}

int main() {
  remove(NOME_ARQUIVO_SOCK);
  int sockfd_server, sockfd_client;
  struct sockaddr_un server_addr, client_addr;
  int len_client_addr = sizeof(client_addr);
  char buffer[MAX_BUFFER];
  int resultado_operacao;

  sockfd_server = socket(AF_UNIX, SOCK_STREAM, 0);
  server_addr.sun_family = AF_UNIX;
  sprintf(server_addr.sun_path, "%s", NOME_ARQUIVO_SOCK);
  bind(sockfd_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(sockfd_server, 5);

  printf("Servidor de pé\n");
  while (1) {
    sockfd_client = accept(sockfd_server, (struct sockaddr *)&client_addr, &len_client_addr);
    read(sockfd_client, &buffer, MAX_BUFFER);

    mensagem_t* requisicao = desserializar_mensagem(buffer);
    resultado_operacao = operar(requisicao->cabecalho[0], requisicao->dados);
    printf("Operação: %d %c %d = %d\n", requisicao->dados[0], obter_operador(requisicao->cabecalho[0]), requisicao->dados[1], resultado_operacao);


    mensagem_t* resposta = malloc(sizeof(mensagem_t) + sizeof(int8_t));
    resposta->cabecalho[0] = requisicao->cabecalho[0];
    resposta->cabecalho[1] = 1;
    resposta->dados[0] = resultado_operacao;
    serializar_mensagem(buffer, resposta);

    write(sockfd_client, &buffer, MAX_BUFFER);
    close(sockfd_client);
  }
}
