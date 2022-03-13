/*
 * #include <stdlib.h>
 * void exit(int status);
 *
 * #include <unistd.h>
 * void _exit(int status);
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  printf("flushed\n");
  printf("after flushed");

  exit(0);
  // _exit(0);
}
