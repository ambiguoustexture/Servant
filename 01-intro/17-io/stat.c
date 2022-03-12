/*
 * #include <sys/stat.h>
 *
 * int  stat(const char *pathname, struct stat *statbuf);
 * int lstat(const char *pathname, struct stat *statbuf);
 */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc == 2) {
    struct stat statbuf;
    if (stat(argv[1], &statbuf) == -1) {
      perror("stat");
      return -1;
    }
    printf("size: %d\n", statbuf.st_size);
  } else {
    printf("usage: ./stat file\n");
    return -1;
  }

  return 0;
}
