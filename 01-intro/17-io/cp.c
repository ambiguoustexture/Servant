/*
 * ssize_t read(int fd, void *buf, size_t count);
 *     fd:    fd of src
 *     buf:   ptr of dest
 *     count: size of byte to be read
 * ssize_t write(int fd, const void *buf, size_t count);
 *     fd:    fd of dest
 *     buf:   ptr of src
 *     count: size of byte to be written
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int arg, char **argv) {
  int fd_src = open(argv[1], O_RDONLY);
  {
    if (fd_src == -1) {
      perror("open");
      return -1;
    }

    int fd_dst = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if (fd_dst == -1) {
      perror("write");
      return -1;
    }

    char buf[1024] = {0};
    int len = 0;
    while ((len = read(fd_src, buf, sizeof(buf)) > 0)) {
      write(fd_dst, buf, len);
    }

    close(fd_dst);
    close(fd_src);
  }
  return 0;
}
