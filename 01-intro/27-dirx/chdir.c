/*
 * #include <unistd.h>
 * int chdir(const char *path);
 *
 * #include <unistd.h>
 * char *getcwd(char *buf, size_t size);
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char buf[128];
  getcwd(buf, sizeof(buf));
  printf("current working directory: %s\n", buf);

  if (mkdir("subdir", 0761) == -1) {
    perror("mkdir");
    return -1;
  } else {
    printf("\"mkdir subdir\" successed\n");

    if (chdir("./subdir") == -1) {
      perror("chdir");
      return -1;
    }
    printf("\"cd ./subdir\" successed\n");
    getcwd(buf, sizeof(buf));
    printf("current working directory: %s\n", buf);

    int fd = open("nested.txt", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
      perror("open");
      return -1;
    }
    close(fd);
    printf("nested.txt created\n");

    // if (remove("nested.txt") == -1) {
    //   perror("remove");
    //   return -1;
    // }
    // printf("nested.txt removed\n");

    if (chdir("../") == -1) {
      perror("chdir");
      return -1;
    }
    printf("unnested, back to ..\n");

    // if (rmdir("./subdir") == -1) {
    //   perror("rmdir");
    //   return -1;
    // }
    // printf("subdir removed\n");

    getcwd(buf, sizeof(buf));
    printf("current working directory: %s\n", buf);
  }
  return 0;
}
