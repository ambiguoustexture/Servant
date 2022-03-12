#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int oldfd = open("a.txt", O_RDWR | O_CREAT, 0664);
  int newfd = dup(oldfd);

  if (newfd == -1) {
    perror("dup");
    return -1;
  }
  printf("oldfd: %d\nnewfd: %d\n", oldfd, newfd);
  close(oldfd);

  char *str = "hello,world\n";
  if (write(newfd, str, strlen(str)) == -1) {
    perror("write");
    return -1;
  }
  close(oldfd);

  return 0;
}
