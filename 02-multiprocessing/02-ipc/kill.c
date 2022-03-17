#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  pid_t pid = fork();

  if (pid == 0) {
    int i = 0;
    for (i = 0; i < 5; i++) {
      printf("child  process\n");
      sleep(1);
    }

  } else if (pid > 0) {
    printf("parent process\n");
    sleep(2);
    kill(pid, SIGINT);
    printf("child  process killed\n");
  }

  return 0;
}
