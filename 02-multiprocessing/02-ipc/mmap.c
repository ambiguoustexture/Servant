#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd = open("a.txt", O_RDWR);
  int size = lseek(fd, 0, SEEK_END);

  void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    exit(0);
  }

  pid_t pid = fork();
  if (pid > 0) {
    // parent process

    // wait for child proess
    wait(NULL);
    char buf[64];
    strcpy(buf, (char *)ptr);
    printf("data from mapped memory: %s\n", buf);
  } else if (pid == 0) {
    // child  process
    strcpy((char *)ptr, "data from process");
  }
  munmap(ptr, size);

  return 0;
}
