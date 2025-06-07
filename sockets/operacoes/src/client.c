#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "protocolo/protocolo.h"

void obter_dados_operacao(mensagem_t* requisicao) {
  int opr, op1, op2;
  printf("0 - Soma\n1 - Subtração\n2 - Multiplicação\n3 - Divisão\n\n");

  printf("Operador:\n");
  scanf("%d", &opr);
  printf("Operando 1:\n");
  scanf("%d", &op1);
  printf("Operando 2:\n");
  scanf("%d", &op2);

  requisicao->cabecalho[0] = (char)opr;
  requisicao->cabecalho[1] = 2;
  requisicao->dados[0] = (char)op1;
  requisicao->dados[1] = (char)op2;
}

int main() {
  int sockfd;
  int resultado;
  struct sockaddr_un server_addr;
  char buffer[MAX_BUFFER];

  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  server_addr.sun_family = AF_UNIX;
  sprintf(server_addr.sun_path, "%s", NOME_ARQUIVO_SOCK);
  connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  mensagem_t* requisicao = malloc(sizeof(mensagem_t) + sizeof(int8_t) * 2); 
  obter_dados_operacao(requisicao);

  serializar_mensagem(buffer, requisicao);
  write(sockfd, &buffer, MAX_BUFFER);
  read(sockfd, &buffer, MAX_BUFFER);
  mensagem_t* resposta = desserializar_mensagem(buffer);

  printf("Resultado da operação: %d\n", resposta->dados[0]);
}
