## Intro

### Standard C Library IO Functions (in manual section 3)
- libc with "f" as prefix.
- libc with flush.
- Anything as file with fd(file descriptor).

### Virtual Address Space
- Linux Kernal
  - memory manage
  - process manage
  - device driver manage
  - virtual file manage
- User Space
  - env
  - argc, argv
  - stack
  - shared library
  - heap
  - .bss (uninitialized global variables)      |
  - .data (initialized global variables)       | Executable and Linkable file
  - .text (codes, binary machine instructions) |
  - protected address space


### File Descriptor
-------------------------------
Linux Kernal                  |
    Process Control Block     |
        File Descriptor Table |
-------------------------------
- 0: STDIN_FILENO  |
- 1: STDOUT_FILENO | /dev/tty (open by default)
- 2: STDERR_FILENO |
- ...
- 1023 (max size by default)

### Linux System IO Functions (in manual section 2)

#### open & close
```C
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int close(int fd);
```

#### read & write
```C
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
```
#### lseek
```C
off_t lseek(int fd, off_t offset, int whence);
```
#### stat & lstat
```C
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
```
