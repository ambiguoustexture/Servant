#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid > 0) {
    printf("parent process: %d\n", getpid());
    sleep(1);
  } else if (pid == 0) {
    printf("child  process: %d under %d\n", getpid(), getppid());
    // execlp(const char *file,     const char *arg, .../*, (char *) NULL */);
    execlp("echo", "echo", "child  process: echo", NULL);
    perror("execlp");
    printf("child  process: %d\n", getpid());
  }
  printf("task from process: %d\n", getpid());

  return 0;
}
