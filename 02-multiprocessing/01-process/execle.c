#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid > 0) {
    printf("parent process: %d\n", getpid());
    sleep(1);
  } else if (pid == 0) {
    printf("child  process: %d under %d\n", getpid(), getppid());
    // execle( const char *pathname, const char *arg, .../*, (char *) NULL, 
    //   char *const envp[] */); 
    // char *const envp[] = {".", NULL};
    // char *const envp[] = {"", NULL};
    char *const envp = {NULL};
    execle("ech0", "ech0", "child  process: ech0", NULL, envp);
    perror("execlp");
    printf("child  process: %d\n", getpid());
  }
  printf("task from process: %d\n", getpid());

  return 0;
}
