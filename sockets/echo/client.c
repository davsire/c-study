#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER 256

int main() {
  int sockfd, sockres;
  struct sockaddr_in server_addr;
  char buffer[MAX_BUFFER];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(1100);
  sockres = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (sockres == -1) {
    printf("Erro ao conectar com servidor..\n");
    return 0;
  }

  scanf("%s", buffer);
  write(sockfd, &buffer, MAX_BUFFER);
  int nbytes = read(sockfd, &buffer, MAX_BUFFER);
  buffer[nbytes] = '\0';
  printf("ECHO: %s\n", buffer);
  close(sockfd);
}
