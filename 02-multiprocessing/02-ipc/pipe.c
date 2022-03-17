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
    printf("parent process: %d\n", getpid());

    close(fd[1]);
    char buf[1024] = {0};
    read(fd[0], buf, sizeof(buf));

    printf("parent process: %d recv: %s\n", getpid(), buf);
  } else if (pid == 0) {
    printf("child  process: %d\n", getpid());

    close(fd[0]);
    char *str = "hello from child";
    write(fd[1], str, strlen(str));
  }
  return 0;
}
