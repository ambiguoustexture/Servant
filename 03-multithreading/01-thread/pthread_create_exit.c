#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg) {
  printf("\t\t\t|child thread: %ld\n", pthread_self());
  printf("\t\t\t|child thread: %ld pass in: %d by reference\n", pthread_self(),
         *(int *)arg);

  printf("\t\t\t|child thread: %ld exited\n", pthread_self());
}

int main() {
  printf("|main thread: %ld\n", pthread_self());
  int num = 42;

  pthread_t tid;
  int ret = pthread_create(&tid, NULL, callback, (void *)&num);
  if (ret != 0) {
    printf("error : %s\n", strerror(ret));
  }

  // make main thread live longer than child thread in a simple and naive way
  // (not recommanded)
  // sleep(1);

  printf("|main thread: %ld exited\n", pthread_self());
  // terminate main thread with NULL as specified thread id
  pthread_exit(NULL);

  return 0;
}
