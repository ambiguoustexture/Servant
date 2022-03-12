#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // 1. duplicate file descriptor
  int oldfd = open("a.txt", O_CREAT, 0666);
  if (oldfd == -1) {
    perror("open O_CREAT");
    return -1;
  }
  int newfd = fcntl(oldfd, F_DUPFD);
  if (newfd == -1) {
    perror("fcntl F_DUPFD");
    return -1;
  }
  close(oldfd);
  close(newfd);

  // 2. control file over descriptors

  int fd = open("a.txt", O_RDWR);
  if (fd == -1) {
    perror("open O_RDWR");
    return -1;
  }

  const char *buf = "write without O_APPEND\n";
  if (write(fd, buf, sizeof(buf))) {
    printf("write without O_APPEND flag failed\n");
  }

  // get flag
  int flag = fcntl(fd, F_GETFL);
  if (flag == -1) {
    perror("fcntl F_GETFL");
    return -1;
  }
  flag |= O_APPEND;

  // set flag
  if (fcntl(fd, F_SETFL, flag) == -1) {
    perror("fcntl F_SETFL O_APPEND");
    return -1;
  }

  const char *str = "hello\n";
  if (write(fd, str, strlen(str)) != -1) {
    printf("write with O_APPEND(set by fcntl) successed\n");
  }

  close(fd);

  return 0;
}
