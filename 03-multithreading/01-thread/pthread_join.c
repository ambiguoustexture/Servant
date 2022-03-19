#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int value = 42;

void *callback(void *arg) {
  printf("\t\t\t|child thread: %ld\n", pthread_self());
  value++;

  pthread_exit((void *)&value); // return (void *)&value;
}

int main() {
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, callback, NULL);

  if (ret != 0) {
    char *errstr = strerror(ret);
    printf("error : %s\n", errstr);
  }

  printf("|main thread: %ld\n", pthread_self());

  int *thread_retval;
  ret = pthread_join(tid, (void **)&thread_retval);
  if (ret != 0) {
    char *errstr = strerror(ret);
    printf("error : %s\n", errstr);
  }

  printf("|main thread: %ld, get %d from child thread\n", pthread_self(),
         *thread_retval);

  pthread_exit(NULL);

  return 0;
}
