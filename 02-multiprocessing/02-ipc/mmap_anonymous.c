#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEN_MAX 4096

int main() {
  // int len = 4096;
  void *ptr = mmap(NULL, LEN_MAX, PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS, -1 /* fd */, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap MAP_ANONYMOUS");
    exit(0);
  }

  pid_t pid = fork();
  if (pid > 0) {
    printf("parent process: %d", getpid());
    strcpy((char *)ptr, "data");
    wait(NULL);
  } else if (pid == 0) {
    sleep(1);
    printf("child  process: %d get: %s from parent process: %d\n", getpid(),
           (char *)ptr, getppid());
  }

  if (munmap(ptr, LEN_MAX) == -1) {
    perror("munmap");
    exit(0);
  }
  return 0;
}
