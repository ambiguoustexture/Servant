#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int oldfd = open("left.txt", O_RDWR | O_CREAT, 0664);
  if (oldfd == -1) {
    perror("open");
    return -1;
  }

  int newfd = open("right.txt", O_RDWR | O_CREAT, 0664);
  if (newfd == -1) {
    perror("open");
    return -1;
  }

  printf("oldfd: %d\nnewfd: %d\n", oldfd, newfd);

  // redirect oldfd to newfd
  int latestfd = dup2(oldfd, newfd);
  if (latestfd == -1) {
    perror("dup2");
    return -1;
  }

  char *str = "hello, dup2";
  if (write(newfd, str, strlen(str)) == -1) {
    perror("write");
    return -1;
  }

  printf("oldfd: %d\nnewfd: %d\nlatestfd: %d\n", oldfd, newfd, latestfd);

  close(oldfd);
  close(newfd);

  return 0;
}
