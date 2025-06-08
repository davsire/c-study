#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define PORTA_SERVIDOR 1100
#define MAX_CLIENTES 10
#define MAX_BUFFER 4096

int main() {
  int server_fd, new_fd;
  struct sockaddr_in server_addr, new_addr;
  socklen_t new_addr_len = sizeof(new_addr);
  struct pollfd clientes[MAX_CLIENTES + 1];
  char buffer[MAX_BUFFER];
  char msg_formatada[MAX_BUFFER];
  int nbytes;
  int clientes_ativos = 0;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("Erro ao criar socket do servidor...\n");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORTA_SERVIDOR);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    printf("Erro ao associar servidor na porta %d...\n", PORTA_SERVIDOR);
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) == -1) {
    printf("Erro ao iniciar servidor para conexões...\n");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i <= MAX_CLIENTES; i++) {
    clientes[i].fd = -1;
  }

  clientes[0].fd = server_fd;
  clientes[0].events = POLLIN;

  printf("Servidor de chat iniciado!\n");
  while (1) {
    if (poll(clientes, MAX_CLIENTES + 1, -1) == -1) {
      printf("Erro ao fazer polling dos clientes...\n");
      close(server_fd);
      exit(EXIT_FAILURE);
    }

    if (clientes[0].revents & POLLIN) {
      new_fd = accept(server_fd, (struct sockaddr *)&new_addr, &new_addr_len);

      if (new_fd < 0) {
        printf("Erro ao aceitar novo cliente...\n");
        continue;
      }

      if (clientes_ativos == MAX_CLIENTES) {
        sprintf(msg_formatada, "O chat atingiu seu limite de conexões... Volte mais tarde!");
        write(new_fd, &msg_formatada, sizeof(msg_formatada));
        close(new_fd);
        continue;
      }

      printf("Novo cliente no chat, ID: %d\n", new_fd);
      for (int i = 1; i <= MAX_CLIENTES; i++) {
        if (clientes[i].fd == -1) {
          clientes_ativos++;
          clientes[i].fd = new_fd;
          clientes[i].events = POLLIN;
          sprintf(msg_formatada, "Conexão estabelecida com o chat, seu ID é: %d", new_fd);
          write(new_fd, &msg_formatada, sizeof(msg_formatada));
          break;
        }
      }
    }

    for (int i = 1; i <= MAX_CLIENTES; i++) {
      if (clientes[i].fd != -1 && (clientes[i].revents & POLLIN)) {
        nbytes = read(clientes[i].fd, &buffer, MAX_BUFFER);

        if (nbytes == 0) {
          printf("Cliente ID %d desconectado\n", clientes[i].fd);
          close(clientes[i].fd);
          clientes[i].fd = -1;
          clientes_ativos--;
          continue;
        }

        buffer[nbytes] = '\0';
        snprintf(msg_formatada, MAX_BUFFER, "Cliente ID %d diz: %s", clientes[i].fd, buffer);
        printf("%s\n", msg_formatada);

        for (int j = 1; j <= MAX_CLIENTES; j++) {
          if (clientes[j].fd != -1 && clientes[j].fd != clientes[i].fd) {
            write(clientes[j].fd, &msg_formatada, sizeof(msg_formatada));
          }
        }
      }
    }
  }

  close(server_fd);
  exit(EXIT_SUCCESS);
}
