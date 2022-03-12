#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int count_regdt(const char *);

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("usage: %s dir\n", argv[0]);
    return -1;
  }
  printf("count of regular file：%d\n", count_regdt(argv[1]));

  return 0;
}

int count_regdt(const char *path) {
  DIR *dir = opendir(path);

  if (dir == NULL) {
    perror("opendir");
    exit(0);
  }

  int count = 0;
  struct dirent *direntp;
  while ((direntp = readdir(dir)) != NULL) {
    char *d_name = direntp->d_name;
    if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0)
      continue;

    if (direntp->d_type == DT_DIR) {
      char newpath[256];
      sprintf(newpath, "%s/%s", path, d_name);
      count += count_regdt(newpath);
    }

    if (direntp->d_type == DT_REG)
      count++;
  }
  closedir(dir);

  return count;
}
