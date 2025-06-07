#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

int soma_medicoes = 0, numero_medicoes = 0;

void* monitoramento() {
  while (1) {
    printf("Número de medições: %d --- Média: %.2f\n", numero_medicoes, numero_medicoes > 0 ? (float)soma_medicoes / numero_medicoes : 0);
    sleep(1);
  }
}

int main() {
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int nbytes;
  char buffer[1];
  pthread_t monitor;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(1100);
  bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  pthread_create(&monitor, NULL, monitoramento, NULL);

  while (1) {
    nbytes = recvfrom(sockfd, &buffer, 1, MSG_WAITALL, (struct sockaddr *)&client_addr, &client_addr_len); 
    if (nbytes > 0) {
      numero_medicoes++;
      soma_medicoes += buffer[0];
    }
  }
}
