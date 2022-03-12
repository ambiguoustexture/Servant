/*
 * #include <sys/stat.h>
 *
 * change mode of file
 * int chmod(const char *pathname, mode_t mode);
 */

#include <stdio.h>
#include <sys/stat.h>

int main() {
  if (chmod("makefile", 0666)) {
    perror("chmod");
    return -1;
  }

  return 0;
}
