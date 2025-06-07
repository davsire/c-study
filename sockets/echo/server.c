#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER 256

int main() {
  int sockfd_server, sockfd_client;
  struct sockaddr_in server_addr, client_addr;
  char buffer[MAX_BUFFER];

  sockfd_server = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(1100);
  bind(sockfd_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(sockfd_server, 5);

  while (1) {
    printf("Aguardando requisições...\n");
    int len = sizeof(client_addr);
    sockfd_client = accept(sockfd_server, (struct sockaddr *)&client_addr, &len);
    int nbytes = read(sockfd_client, &buffer, MAX_BUFFER);
    buffer[nbytes] = '\0';
    printf("Mensagem do cliente: %s\n", buffer);
    write(sockfd_client, &buffer, nbytes);
    close(sockfd_client);
  } 
}
