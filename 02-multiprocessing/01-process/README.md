# Multiprocessing

## Parallelism vs Concurrency
Considering a single-core CPU (without Hyper-Threading or Instruction-level parallelism),
parallelism could never be possible.

## Processing Control Block
In the Linux kernel, each process is represented by a `task_struct` in a doubly-linked list,
the head of which is `init_task` (pid 0, not pid 1).
This is commonly known as the process table.
```C
// linux/sched.h

struct task_struct {...};
```
In user mode, the process table is visible to normal users under `/proc` .
```Shell
> ls /proc/1
...
arch_status  comm                fd        map_files   ns             projid_map  smaps_rollup  timens_offsets
attr         coredump_filter     fdinfo    maps        numa_maps      root        stack         timers
autogroup    cpu_resctrl_groups  gid_map   mem         oom_adj        sched       stat          timerslack_ns
auxv         cpuset              io        mountinfo   oom_score      schedstat   statm         uid_map
cgroup       cwd                 latency   mounts      oom_score_adj  sessionid   status        wchan
clear_refs   environ             limits    mountstats  pagemap        setgroups   syscall
cmdline      exe                 loginuid  net         personality    smaps       task
```


### misc
```Shell
# ulimit — set or report file size limit
> ulimit -a
-t: cpu time (seconds)              unlimited
-f: file size (blocks)              unlimited
-d: data seg size (kbytes)          unlimited
-s: stack size (kbytes)             8192
-c: core file size (blocks)         unlimited
-m: resident set size (kbytes)      unlimited
-u: processes                       7843
-n: file descriptors                1024
-l: locked-in-memory size (kbytes)  8192
-v: address space (kbytes)          unlimited
-x: file locks                      unlimited
-i: pending signals                 7843
-q: bytes in POSIX msg queues       819200
-e: max nice                        0
-r: max rt priority                 0
-N 15:                              unlimited
```
## Task State
```Shell
# ps - report a snapshot of the current processes.
# To see every process on the system using BSD syntax:
> ps axu
# To see every process on the system using BSD syntax with Jobs format:
> ps ajx

# Abbreviation of process states:
D Uninterruptible sleep (usually IO)
R Running or runnable (on run queue)
S Interruptible sleep (waiting for an event to complete)
T Stopped, either by a job control signal or because it is being traced.
W paging (not valid since the 2.6.xx kernel)
X dead (should never be seen)
Z Defunct ("zombie") process, terminated but not reaped by its parent.

# Additional informations:
# < high-priority (not nice to other users)
# N low-priority (nice to other users)
# L has pages locked into memory (for real-time and custom IO)
# s is a session leader
# l is multi-threaded (using CLONE_THREAD, like NPTL pthreads do)
# + is in the foreground process group

> cat /proc/1/stat
1 (systemd) S 0 1 1 0 -1 4194560 34076 22493191 26 2061 264 236 175450 28510 20 0 1 0 3 112775168 3123 18446744073709551615 1 1 0 0 0 0 671173123 4096 1260 0 0 0 17 1 0 0 0 0 0 0 0 0 0 0 0 0 0

# top - display Linux processes
> top/htop/btop

# kill - terminate a process
> kill -l
HUP INT QUIT ILL TRAP IOT BUS FPE KILL USR1 SEGV USR2 PIPE ALRM TERM STKFLT CHLD CONT STOP TSTP TTIN TTOU URG XCPU XFSZ VTALRM PROF WINCH POLL PWR SYS
```
## pid & etc.
```Shell
0 scheduler
1 systemd/init (parent process of all user processes)
  |__
  |__
  |__
  | |__...
  |
  ...
2 kthreadd (parent process of all kernel processes)
  |__
  |__
  | |__..
  |
  ...
```

```C
#include <sys/types.h>

// used for storing process IDs, process group IDs, and session IDs
pid_t

#include <unistd.h>

// get the process ID
pid_t getpid(void);

// get the parent process ID
pid_t getppid(void);

// get the process group ID for a process
pid_t getpgid(void);
```
## fork, wait, waitpid - basic process management
- fork: creates a new process by duplicating the calling process.
        The new process is referred to as the child process.
        The calling process is referred to as the parent process.
        The child process and the parent process run in separate memory spaces.
        At the time of fork() both memory spaces have the same content.
        Memory writes, file mappings (mmap()), and unmappings (munmap())
        performed by one of the processes do not affect the other.

- wait: suspends execution of the calling thread(?) until one of its children terminates.
        The call wait(&wstatus) is equivalent to: `waitpid(-1, &wstatus, 0);`

- waitpid: suspends execution of the calling thread(?)
        until a child specified by pid argument
        has changed state.
        By default, waitpid() waits only for terminated children,
        but this behavior is modifiable via the options argument.

### Example from Linux Programmer's Manual
```C
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t cpid, w;
  int wstatus;

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) { /* Code executed by child */
    printf("Child PID is %jd\n", (intmax_t)getpid());
    if (argc == 1)
      pause(); /* Wait for signals */
    _exit(atoi(argv[1]));
  }
  else { /* Code executed by parent */
    do {
      w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
      if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }

      if (WIFEXITED(wstatus)) {
        printf("exited, status=%d\n", WEXITSTATUS(wstatus));
      } else if (WIFSIGNALED(wstatus)) {
        printf("killed by signal %d\n", WTERMSIG(wstatus));
      } else if (WIFSTOPPED(wstatus)) {
        printf("stopped by signal %d\n", WSTOPSIG(wstatus));
      } else if (WIFCONTINUED(wstatus)) {
        printf("continued\n");
      }
    } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    exit(EXIT_SUCCESS);
  }
}
```
```Shell
> ./fork_wait &
Child PID is 32360
[1] 32359
> kill -STOP 32360
stopped by signal 19
> kill -CONT 32360
continued
> kill -TERM 32360
killed by signal 15
[1]+  Done                    ./a.out
>
```
### Virtual Address Space of Parrent Process and Child Process
Considering code below:
```C
int main() {
  mutual_task();
  pid_t pid = fork();
  if (pid == 0) {
    child_task();
  } else if (pid > 0) {
    parent_task();
  }
  mutual_task();
}
```
code executed by parent process:
```C
int main() {
  mutual_task();
  parent_task();
  mutual_task();
}
```
code executed by child process:
```C
int main() {
  mutual_task();
  child_task();
  mutual_task();
}
```

#### NOTES
Under Linux, fork() is implemented using copy-on-write pages, 
so the only penalty that it incurs is the time and memory required to duplicate the parent's page tables, 
and to create a unique task structure for the child.

##### C library/kernel differences
Since version 2.3.3, rather than invoking the kernel's fork() system call, 
the glibc fork() wrapper that is provided as part of the NPTL threading implementation 
invokes clone() with flags that provide the same effect 
as the traditional system call. 
(A call to fork() is equivalent to 
a call to clone() specifying flags as just SIGCHLD.) 
The glibc wrapper invokes any fork handlers 
that have been established using pthread_atfork().

### [Debugging programs with multiple processes](https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_25.html)
By default, when a program forks, 
GDB will continue to debug the parent process and the child process will run unimpeded.

If you want to follow the child process instead of the parent process, 
use the command `set follow-fork-mode`.

`set follow-fork-mode [mode]`: Set the debugger response to a program call of fork() or vfork(). 
A call to fork or vfork creates a new process. The mode can be:
- parent: The original process is debugged after a fork(). 
          The child process runs unimpeded. This is the default.
- child:  The new process is debugged after a fork. The parent process runs unimpeded.
- ask:    The debugger will ask for one of the above choices.

`show follow-fork-mode`: Display the current debugger response to a fork() or vfork() call.

`detach-on-fork [mode]`: [Specifies whether GDB should debug both parent and child process after a call to fork() or vfork()](https://visualgdb.com/gdbreference/commands/set_detach-on-fork).
- on: In this mode GDB will continue being attached to either 
      parent or child process (depending on the `set follow-fork-mode` command.
- off: In this mode GDB will be attached to both processes after a call to fork() or vfork(). 
       Use the info inferiors command to show details and the inferior command to switch between them.

## exec & etc.
The exec() family of functions replaces the current process image with a new process image.
The functions described in this manual page are layered on top of execve().
The initial argument for these functions is the name of a file that is to be executed.
```C
#include <unistd.h>

extern char **environ;

// 'l'
// The const char *arg and subsequent ellipses can be thought of as arg0, arg1, ..., argn.
// Together they describe a list of one or more pointers to null-terminated strings
// that represent the argument list available to the executed program.
// The first argument, by convention,
// should point to the filename associated with the file being executed.
// The list of arguments must be terminated by a null pointer,
// and, since these are variadic functions, this pointer must be cast (char *) NULL.

int execl(  const char *pathname, const char *arg, .../*, (char *) NULL */);
int execlp( const char *file,     const char *arg, .../*, (char *) NULL */);
int execle( const char *pathname, const char *arg, .../*, (char *) NULL, char *const envp[] */);

// 'v'
// By contrast with the 'l' functions,
// the 'v' functions specify the command-line arguments of the executed program as a vector.
// The char *const argv[] argument is an array of pointers to null-terminated strings
// that represent the argument list available to the new program.
// The first argument, by convention,
// should point to the filename associated with the file being executed.
// The array of pointers must be terminated by a null pointer.

int execv(  const char *pathname, char *const argv[]);
int execvp( const char *file,     char *const argv[]);
int execvpe(const char *file,     char *const argv[], char *const envp[]);
`
// 'p'
// These 'p' functions duplicate the actions of the shell in searching for an executable file
// if the specified filename does not contain a slash (/) character.
// The file is sought in the colon-separated list of directory pathnames
// specified in the PATH environment variable.
// If this variable isn't defined, the path list defaults to a list
// that includes the directories returned by 
// confstr(_CS_PATH) (which typically returns the value "/bin:/usr/bin")
// and possibly also the current working directory.

// 'e'
// The environment of the new process image is specified via the argument envp.
// The envp argument is an array of pointers to null-terminated strings
// and must be terminated by a null pointer.
// All other exec() functions (which do not include 'e' in the suffix) 
// take the environment for the new process image 
// from the external variable environ in the calling process.
```
## process control

### exit vs _exit
Most C programs call the library routine `exit()`, 
which flushes buffers, closes streams, unlinks temporary files, etc., before calling `_exit()`.
```C
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
```

### Orphan Process
A child process which is reclaimed by systemd/init(pid = 1) 
when the original parent process terminates before the child.

### Zombie Process
A child process which is created 
when a parent process does not use the `wait` system call 
after a child dies to read its exit status. 
A zombie proces can't be killed by `kill -9`.
