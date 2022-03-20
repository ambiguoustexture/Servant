#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int items = 144;

pthread_mutex_t mutex;

void *consume(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    if (items > 0) {
      usleep(2022);
      // 2. re-lock
      pthread_mutex_lock(&mutex);
      printf("thread: %ld is consumeing the %-5d item\n", pthread_self(),
             --items);
      // 1. un-lock
      pthread_mutex_unlock(&mutex);
    } else {
      pthread_mutex_unlock(&mutex);
      break;
    }
  }

  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);

  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, consume, NULL);
  pthread_create(&tid2, NULL, consume, NULL);
  pthread_create(&tid3, NULL, consume, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  pthread_detach(tid1);
  pthread_detach(tid2);
  pthread_detach(tid3);

  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);

  return 0;
}
