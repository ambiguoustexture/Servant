#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("fifo", O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(0);
  }

  while (1) {
    char buf[1024] = {0};
    int len = read(fd, buf, sizeof(buf));
    if (len == 0) {
      printf("read failed ...\n");
      break;
    }
    printf("read  fifo: %s\n", buf);
  }

  close(fd);

  return 0;
}
