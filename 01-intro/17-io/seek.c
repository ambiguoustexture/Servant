/* reposition read/write file offset
 * return the final offsest
 *
 * lseek(int __fd, __off_t __offset, int __whence);
 *     __fd:     fd by open()
 *     __offset:
 *     __whence:
 *         SEEK_SET: begin of file + __offset
 *         SEEK_CUR: current offset + __offset
 *         SEEK_END: size of file + __offset
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd = open(argv[1], O_RDWR);
  {
    if (fd == -1) {
      perror("open");
      return -1;
    }

    if (lseek(fd, 100, SEEK_END) == -1) {
      perror("lseek");
      return -1;
    }
    if (write(fd, "appended\n", 9) == -1) {
      perror("append");
      return -1;
    }
  }
  close(fd);
}
