## Condition Variables and Semaphore 

### Condition Variables 
```C
#include <pthread.h> 

int pthread_cond_init(pthread_cond_t *restrict cond, 
        const pthread_condattr_t *restrict attr);

int pthread_cond_destroy(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *restrict cond, 
        pthread_mutex_t *restrict mutex);

int pthread_cond_timedwait(pthread_cond_t *restrict cond, 
        pthread_mutex_t *restrict mutex, 
        const struct timespec *restrict abstime);

int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_broadcast(pthread_cond_t *cond);

```

### Semaphore 
```C
#include <semaphore.h>

int    sem_getvalue(sem_t *restrict, int *restrict);
int    sem_init(sem_t *, int, unsigned);
int    sem_destroy(sem_t *);

sem_t *sem_open(const char *, int, ...);
int    sem_close(sem_t *);

// lock a semaphore
int    sem_wait(sem_t *);
int    sem_timedwait(sem_t *restrict, const struct timespec *restrict);
int    sem_trywait(sem_t *);

// unlock a semaphore
int    sem_post(sem_t *);

// remove a named semaphore
int    sem_unlink(const char *);
```

