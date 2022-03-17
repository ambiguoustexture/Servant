# Inter Process Communication (IPC)
- anonymous pipe
- named pipe (FIFO)
- signal
- message queue
- shared memory
- semaphore
- socket

## Anonymous Pipe
```C
// pipe – create descriptor pair for interprocess(forked) communication
 
#include <unistd.h>

int pipe(int fildes[2]);

// The pipe() function creates a pipe (
// an object that allows unidirectional data flow) and 
// allocates a pair of file descriptors.  
// The first descriptor connects to the read end of the pipe; 
// the second connects to the write end.
// 
// Data written to fildes[1] appears on (i.e., can be read from) fildes[0].  
// This allows the output of one program to be sent to another program: 
// the source's standard output is set up to be the write end of the pipe; 
// the sink's standard input is set up to be the read end of the pipe.  
// The pipe itself persists until all of its associated descriptors are closed.
// 
// A pipe whose read or write end has been closed is considered widowed.  
// Writing on such a pipe causes the writing process to receive a SIGPIPE signal.  
// Widowing a pipe is the only way to deliver end-of-file to a reader: 
// after the reader consumes any buffered data, reading a widowed pipe returns a zero count.
// The generation of the SIGPIPE signal can be 
// suppressed using the F_SETNOSIGPIPE fcntl command.
```

## Named Pipe(FIFO)
```C
// mkfifo – make a fifo file

#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *path, mode_t mode);

// mkfifo() creates a new fifo file with name path.  
// The access permissions are specified by mode 
// and restricted by the umask() of the calling process.
```

## Memory Map
```C
// mmap – allocate memory, or map files or devices into memory

#include <sys/mman.h>

void * mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
// prot:
//     - PROT_NONE   Pages may not be accessed.
//     - PROT_READ   Pages may be read.
//     - PROT_WRITE  Pages may be written.
//     - PROT_EXEC   Pages may be executed.

// flags:
//     - MAP_ANONYMOUS     Synonym for MAP_ANON.(and -1 as fd)


// The mmap() system call causes the pages 
// starting at addr and continuing for at most len bytes 
// to be mapped from the object described by fd, starting at byte offset offset.  
// If offset or len is not a multiple of the pagesize, 
// the mapped region may extend past the specified range.  
// Any extension beyond the end of the mapped object will be zero-filled.
// 
// The addr argument is used by the system 
// to determine the starting address of the mapping, 
// and its interpretation is dependent on the setting of the MAP_FIXED flag.  
// If MAP_FIXED is specified in flags, 
// the system will try to place the mapping at the specified address, 
// possibly removing a mapping that already exists at that location.  
// If MAP_FIXED is not specified, 
// then the system will attempt to use 
// the range of addresses starting at addr 
// if they do not overlap any existing mappings, 
// including memory allocated by malloc() and other such allocators.  
// Otherwise, the system will choose an alternate address 
// for the mapping (using an implementation dependent algorithm) 
// that does not overlap any existing mappings.  
// In other words, without MAP_FIXED the system will attempt
// to find an empty location in the address space 
// if the specified address range has already been mapped by something else.  
// If addr is zero and MAP_FIXED is not specified, 
// then an address will be selected by the system so as 
// not to overlap any existing mappings in the address space.  
// In all cases, the actual starting address of the region is returned.  
// If MAP_FIXED is specified, 
// a successful mmap deletes any previous mapping in the allocated address range.  
// Previous mappings are never deleted if MAP_FIXED is not specified.
```
## Signal
```Shell
> kill -l
...
> man signal
...
```
```C
#include <signal.h>

// simplified software signal facilities
void (*
signal(int sig, void (*func)(int));
)(int);

// or in the equivalent but easier to read typedef'd version:
typedef void (*sig_t) (int);
sig_t signal(int sig, sig_t func);

// send signal to a process
int kill(pid_t pid, int sig);

// send a signal to the caller
int raise(int sig);

// cause abnormal program termination
void abort(void);

// set signal timer alarm
unsigned int alarm(unsigned int seconds);

#include <sys/time.h>

// set the value of an interval timer
int setitimer(int which, const struct itimerval *new_val, struct itimerval *old_value);

// examine and change blocked signals
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);

// examine and change a signal action
int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);
```

## Shared Memory
```C
#include <sys/shm.h>

// get an XSI shared memory segment
int shmget(key_t key, size_t size, int shmflg);

// map/unmap shared memory
void * shmat(int shmid, const void *shmaddr, int shmflg);
int shmdt(const void *shmaddr);

// shared memory control operations
int shmctl(int shmid, int cmd, struct shmid_ds *buf);

// create IPC identifier from path name
#include <sys/ipc.h>

key_t ftok(const char *path, int id);
```

## ipcs
```
ipcs - show information on IPC facilities

ipcs shows information on System V inter-process communication facilities. 
By default it shows information about all three resources: 
    - shared memory segments, 
    - message queues, 
    - semaphore arrays.
```
