#### fcntl – file control
```C
#include <unistd.h>
#include <fcntl.h>

// provides for control over descriptors. 
// The argument fildes is a descriptor to be operated on by cmd.
int fcntl(int fildes, int cmd, ...);
// 1. Locking and Unlocking a File
// 2. Setting the Close-on-Exec Flag
// 3. ...
```
