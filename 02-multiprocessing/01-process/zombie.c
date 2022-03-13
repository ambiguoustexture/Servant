#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid > 0) {
    while (1) {
      printf("parent process: %d, ppid : %d\n", getpid(), getppid());
      sleep(1);
    }
  } else if (pid == 0) {
    printf("child  process: %d, ppid : %d\n", getpid(), getppid());
  }
  return 0;
}
