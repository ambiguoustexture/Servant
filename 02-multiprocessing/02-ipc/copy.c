#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd_src = open(argv[1], O_RDWR);
  if (fd_src == -1) {
    perror("open");
    exit(0);
  }

  int len = lseek(fd_src, 0, SEEK_END);

  int fd_dst = open(argv[2], O_RDWR | O_CREAT, 0664);
  if (fd_dst == -1) {
    perror("open");
    exit(0);
  }

  truncate(argv[2], len);
  // seems useless
  // write(fd_dst, " ", 1);

  void *ptr_src =
      mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_src, 0);
  void *ptr_dst =
      mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);

  if (ptr_src == MAP_FAILED) {
    perror("mmap");
    exit(0);
  }

  if (ptr_dst == MAP_FAILED) {
    perror("mmap");
    exit(0);
  }

  memcpy(ptr_dst, ptr_src, len);

  munmap(ptr_dst, len);
  munmap(ptr_src, len);

  close(fd_dst);
  close(fd_src);

  return 0;
}
