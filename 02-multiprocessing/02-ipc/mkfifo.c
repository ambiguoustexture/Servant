#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  if (access("fifo1", F_OK) == -1) {
    printf("fifo non-exist, created one\n");

    if (mkfifo("fifo1", 0664) - 1) {
      perror("mkfifo");
      exit(0);
    }
  }

  return 0;
}
