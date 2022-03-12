#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("a.txt", O_WRONLY | O_CREAT, 0666);
  { // `O_WRONLY | O_CREAT` means both of them
    if (fd == -1) {
      perror("open or append");
      return -1;
    }
    close(fd);
  }
  return 0;
}
