#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid > 0) {
    printf("parent process: %d\n", getpid());
    sleep(1);
  } else if (pid == 0) {
    printf("child  process: %d under %d\n", getpid(), getppid());
    // execl(const char *pathname, const char *arg, .../*, (char *) NULL */);
    execl("/bin/echo", "echo", "child  process: echo", NULL);
    perror("execl");
    printf("child  process: %d\n", getpid());
  }
  printf("task from process: %d\n", getpid());

  return 0;
}
