#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
  srand(time(NULL));
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[1];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(1100);
  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    printf("Erro ao conectar ao servidor...\n");
    exit(0);
  }

  buffer[0] = rand() % 10;
  printf("Meu número: %d\n", buffer[0]);
  sleep(8);
  write(sockfd, &buffer, 1);
  read(sockfd, &buffer, 1);
  printf("Número do servidor: %d\n", buffer[0]);
  close(sockfd);
}
