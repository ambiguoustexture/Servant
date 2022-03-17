#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int ret = access("fifo", F_OK);
  if (ret == -1) {
    printf("fifo non-exist, create one\n");

    if (mkfifo("fifo", 0664) == -1) {
      perror("mkfifo");
      exit(0);
    }
  }

  int fd = open("fifo", O_WRONLY);
  if (fd == -1) {
    perror("open");
    exit(0);
  }

  for (int i = 0; i < 100; i++) {
    char buf[1024];
    sprintf(buf, "rec[%d]", i);
    printf("write fifo: %s\n", buf);
    write(fd, buf, strlen(buf));
    sleep(1);
  }

  close(fd);

  return 0;
}
