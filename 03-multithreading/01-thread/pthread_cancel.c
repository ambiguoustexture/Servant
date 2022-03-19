#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void *callback(void *arg) {
  printf("\t\t\t|child thread: %ld before cancellation point\n",
         pthread_self());
  sleep(1);
  printf("\t\t\t|child thread: %ld after  cancellation point\n",
         pthread_self());
}

int main() {
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, callback, NULL);
  if (ret != 0) {
    char *errstr = strerror(ret);
    printf("error : %s\n", errstr);
  }

  ret = pthread_cancel(tid);
  if (ret != 0) {
    char *errstr = strerror(ret);
    printf("error : %s\n", errstr);
  }

  printf("|main thread: %ld\n", pthread_self());

  pthread_exit(NULL);

  return 0;
}
