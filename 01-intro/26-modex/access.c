/*
 * #include <unistd.h>
 *
 * check accessibility of a file
 * int access(const char *pathname, int mode);
 *     mode:
 *         R_OK:
 *         W_OK:
 *         X_OK:
 *         F_OK: is existed
 */

#include <stdio.h>
#include <unistd.h>

int main() {
  if (access("makefile", F_OK) == -1) {
    perror("access");
  }

  printf("file existed!\n");
  return 0;
}
