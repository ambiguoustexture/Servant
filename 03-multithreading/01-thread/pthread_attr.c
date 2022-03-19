#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg) {
  printf("\t\t\t|child thread: %ld\n", pthread_self());
}

int main() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  pthread_t tid;
  int ret = pthread_create(&tid, &attr, callback, NULL);
  if (ret != 0) {
    char *errstr = strerror(ret);
    printf("error : %s\n", errstr);
  }

  size_t size;
  pthread_attr_getstacksize(&attr, &size);
  printf("|main thread: %ld with %ld as call stack size\n", pthread_self(),
         size, tid);

  pthread_attr_destroy(&attr);
  pthread_exit(NULL);

  return 0;
}
