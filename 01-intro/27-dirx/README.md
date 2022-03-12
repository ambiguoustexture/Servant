#### make, remove, rename, get directory
```C
// make a directory file
int mkdir(const char *pathname, mode_t mode);

// remove a directory file
int rmdir(const char *pathname);

// rename a directory file
int rename(const char *oldpath, const char *newpath);

// change current working directory
int chdir(const char *path);

// get working directory pathname
char *getcwd (char *buf, siz_t size);
```

#### open, close directory
```C
#include <sys/types.h>
#include <dirent.h>
DIR *opendir(const char *name);

#include <dirent.h>
struct dirent *readdir(DIR *dirp);

#include <sys/types.h>
#include <dirent.h>
int closedir(DIR *dirp);
```
