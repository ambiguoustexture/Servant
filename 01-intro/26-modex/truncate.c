/*
 * #include <unistd.h>
 * #include <sys/types.h>
 *
 * truncate or extend a file to a specified length
 * int truncate(const char *path, off_t length);
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  if (truncate("a.txt", 5) == -1) {
    perror("truncate");
    return -1;
  }

  return 0;
}
