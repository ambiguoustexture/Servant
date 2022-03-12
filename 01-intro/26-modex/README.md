#### access, chmod, chown, truncate
```C
// check accessibility of a file
int access(const char *pathname, int mode);

// change mode of file
int chmod(const char *filename, int mode);

// change owner and group of a file
int chown(const char *path, uid_t owner, gid t group);

// truncate or extend a file to a specified length
int truncate(const char *path, off_t length);
```
