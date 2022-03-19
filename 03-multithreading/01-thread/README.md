# Multithreading (Light Weight Process as thread)
> A typical process can be thought of as having a single thread of control:
> each process is doing only one thing at a time.
> With multiple threads of control,
> we can design our programs to do more than one thing at a time
> within a single process, with each thread handling a separate task.
```Shell
> ps -Lf pid
UID          PID    PPID     LWP  C NLWP STIME TTY      STAT   TIME CMD
...
```

Forked processes with COW(copy on write),
while multithreading share process's virtual address space except:
- thread id
- signal mask
- thread specific data
- errno
- schedule policies and priority
- call stack, thread local variables and information for function call and link

```Shell
> getconf GNU_LIBPTHREAD_VERSION
# Native POSIX Thread Library
NPTL 2.35
```

## POSIX Thread -- pthread
```Shell
man pthreads
```

```C
#include <pthread.h>
// compile and link with -pthread, (its's ok not to do this, thanks to gcc?).

// create a new thread and on success, return 0; on error, return an error number,
// and the contents of *thread are undefined.

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);

// terminate calling thread
noreturn void pthread_exit(void *retval);

// obtain ID of the calling thread
pthread_t pthread_self(void);

// waits for the thread specified by threadid to terminate.
// If that thread has already terminated, then pthread_join() returns immediately.
// The thread specified by threadid must be joinable.
int pthread_join(pthread_t threadid, void **retval);

// marks the thread identified by threadid as detached.
// When a detached thread terminates,
// its resources are automatically released back to the system
// without the need for another thread to
join with the terminated thread.
int pthread_detach(pthread_t thread)id;

// sends a cancellation request to the thread thread.
// Whether and when the target thread reacts to the cancellation request
// depends on two attributes that are under the control of that thread:
// its cancelability state and type.
int pthread_cancel(pthread_t thread);

// initialize and destroy thread attributes object
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

// ...
```
