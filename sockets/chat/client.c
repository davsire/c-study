#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORTA_SERVIDOR 1100
#define MAX_BUFFER 4096
#define STDIN 0

int main() {
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[MAX_BUFFER];
  fd_set master, fdsleitura;
  int nbytes;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("Erro ao criar socket do cliente...\n");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORTA_SERVIDOR);

  FD_ZERO(&master);
  FD_ZERO(&fdsleitura);

  FD_SET(STDIN, &master);
  FD_SET(sockfd, &master);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    printf("Erro ao se conectar ao chat...\n");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  while (1) {
    fdsleitura = master;

    if (select(sockfd + 1, &fdsleitura, NULL, NULL, NULL) == -1) {
      printf("Erro no select...\n");
      close(sockfd);
      exit(EXIT_FAILURE);  
    }

    if (FD_ISSET(sockfd, &fdsleitura)) {
      nbytes = read(sockfd, &buffer, MAX_BUFFER);

      if (nbytes == 0) {
        printf("Você foi desconectado do chat\n");
        break;
      }

      buffer[nbytes] = '\0';
      printf("%s\n", buffer);
    }

    if (FD_ISSET(STDIN, &fdsleitura)) {
      nbytes = read(STDIN, &buffer, MAX_BUFFER);

      if (nbytes == 0) {
        continue;
      }

      buffer[strcspn(buffer, "\n")] = 0;

      if (strcmp(buffer, "sair") == 0) {
        printf("Saindo do chat...\n");
        break;
      }

      buffer[nbytes] = '\0';
      write(sockfd, &buffer, MAX_BUFFER);
    }
  }

  close(sockfd);
  exit(EXIT_SUCCESS);
}
