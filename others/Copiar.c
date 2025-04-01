#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define PERMISSION 0600

int main(int argc, char *argv[]) {
  int in_fd, out_fd;
  int rd_count, wt_count;
  char buffer[BUFFER_SIZE];

  if (argc != 3) exit(1);
  
  in_fd = open(argv[1], O_RDONLY);
  if (in_fd < 0) exit(2);

  out_fd = creat(argv[2], PERMISSION);
  if (out_fd < 0) exit(3);

  while (1) {
    rd_count = read(in_fd, buffer, BUFFER_SIZE);
    if (rd_count <= 0) break;

    wt_count = write(out_fd, buffer, rd_count);
    if (wt_count <= 0) exit(4);
  }

  close(in_fd);
  close(out_fd);

  if (rd_count < 0) {
    exit(5);
  }

  exit(0);
}
