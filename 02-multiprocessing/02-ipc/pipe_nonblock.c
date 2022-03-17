#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd[2];
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(0);
  }

  pid_t pid = fork();
  if (pid > 0) {
    close(fd[1]);

    // int flags = fcntl(fd[0], F_GETFL);
    // flags |= O_NONBLOCK;
    // fcntl(fd[0], F_SETFL, flags);

    char buf[1024] = {0};

    while (1) {
      int len = read(fd[0], buf, sizeof(buf));
      printf("len : %d\n", len);
      printf("parent recv: %s\n", buf);
      memset(buf, 0, 1024);
      sleep(1);
    }
  } else if (pid == 0) {
    close(fd[0]);
    while (1) {
      const char *str = "hello from child";
      write(fd[1], str, strlen(str));
      sleep(2);
    }
  }
  return 0;
}
