#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  srand(time(NULL));
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[1];

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(1100);

  while (1) {
    buffer[0] = (rand() % 100) + 1;
    printf("Valor medido: %d\n", buffer[0]);
    sendto(sockfd, &buffer, 1, MSG_DONTWAIT, (struct sockaddr *)&server_addr, sizeof(server_addr)); 
    usleep(500000);
  }
}
