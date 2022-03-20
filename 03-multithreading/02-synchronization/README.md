## Thread Synchronization
> When multiple threads of control share the same memory, 
> we need to make sure that each thread sees a consistent view of its data. 
> If each thread uses variables that other threads don’t read or modify, 
> no consistency problems will exist. 
> Similarly, if a variable is read-only, there is no consistency problem 
> with more than one thread reading its value at the same time. 
> However, when one thread can modify a variable 
> that other threads can read or modify, 
> we need to synchronize the threads to ensure 
> that they don’t use an invalid value 
> when accessing the variable’s memory contents.

### Mutex(Mutual Exclusion)
```C
#include <pthread.h>

// lock and unlock a mutex
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);

// lock a read-write lock object for writing
// *writer* has higher priority than reader 
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);

```

### Deadlock
> A thread will deadlock itself if it tries to lock the same mutex twice, 
- un-unlock
- re-lock
> but there are less obvious ways to create deadlocks with mutexes. 
> For example, when we use more than one mutex in our programs, 
> a deadlock can occur if we allow 
> one thread to hold a mutex and block while trying to lock a second mutex at the same time 
> that another thread holding the second mutex tries to lock the first mutex. 
> Neither thread can proceed, 
> because each needs a resource that is held by the other, 
> so we have a deadlock.

### Reference
- [apue3e](http://www.apuebook.com/apue3e.html).
