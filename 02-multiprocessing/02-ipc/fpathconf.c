#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd[2];

  pipe(fd);
  long size = fpathconf(fd[0], _PC_PIPE_BUF);
  printf("pipe size : %ld\n", size);

  return 0;
}
