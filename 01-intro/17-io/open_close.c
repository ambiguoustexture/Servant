/*
#include <fcntl.h>     // io_function()
#include <sys/stat.h>  // flags macro
#include <sys/types.h> // flags macro

// open existed file
int open(const char *pathname, int flags);              // not overrided
function// c// reate a new file int open(const char *pathname, int flags, mode_t
mode); // variadic function in fact

#include <stdio.h>
void perror(const char *s);

*/

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("a.txt", O_RDONLY);
  {
    if (fd == -1) {
      perror("open"); // open: No such file or directory
      return -1;
    } else {
      printf("open: Success\n");
    }
    close(fd);
  }

  return 0;
}
