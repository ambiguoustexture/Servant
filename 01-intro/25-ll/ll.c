/* ll: aliased to ls -lh
 * e.g. ---------- 1 [user] [machine] [size] [human readable time] [name]
 */

#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: ./ll file\n");
    return -1;
  }

  struct stat statbuf;

  if (stat(argv[1], &statbuf) == -1) {
    perror("stat");
    return -1;
  }

  char mode[11] = {'0'};
  {
    switch (statbuf.st_mode & S_IFMT) {
    case S_IFLNK:
      mode[0] = 'l';
      break;
    case S_IFDIR:
      mode[0] = 'd';
      break;
    case S_IFREG:
      mode[0] = '-';
      break;
    case S_IFBLK:
      mode[0] = 'b';
      break;
    case S_IFCHR:
      mode[0] = 'c';
      break;
    case S_IFSOCK:
      mode[0] = 's';
      break;
    case S_IFIFO:
      mode[0] = 'p';
      break;
    default:
      mode[0] = '?';
      break;
    }

    mode[1] = (statbuf.st_mode & S_IRUSR) ? 'r' : '-';
    mode[2] = (statbuf.st_mode & S_IWUSR) ? 'w' : '-';
    mode[3] = (statbuf.st_mode & S_IXUSR) ? 'x' : '-';

    mode[4] = (statbuf.st_mode & S_IRGRP) ? 'r' : '-';
    mode[5] = (statbuf.st_mode & S_IWGRP) ? 'w' : '-';
    mode[6] = (statbuf.st_mode & S_IXGRP) ? 'x' : '-';

    mode[7] = (statbuf.st_mode & S_IROTH) ? 'r' : '-';
    mode[8] = (statbuf.st_mode & S_IWOTH) ? 'w' : '-';
    mode[9] = (statbuf.st_mode & S_IXOTH) ? 'x' : '-';
  }

  int nlink = statbuf.st_nlink;
  char *owner = getpwuid(statbuf.st_uid)->pw_name;
  char *group = getgrgid(statbuf.st_gid)->gr_name;
  long int size = statbuf.st_size;
  char *time = ctime(&statbuf.st_mtime);

  char mtime[512] = {0};
  strncpy(mtime, time, strlen(time) - 1);

  char buf[1024];
  sprintf(buf, "%s %d %s %s %ld %s %s", mode, nlink, owner, group, size, mtime,
          argv[1]);

  printf("%s\n", buf);

  return 0;
}
