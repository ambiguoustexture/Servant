#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex1, mutex2;

void *consuemrA(void *arg) {
  pthread_mutex_lock(&mutex1);
  sleep(1);
  pthread_mutex_lock(&mutex2);

  printf("consumer a consuming ....\n");

  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex1);
  return NULL;
}

void *consumerB(void *arg) {
  pthread_mutex_lock(&mutex2);
  sleep(1);
  pthread_mutex_lock(&mutex1);

  printf("consumer b consuming ....\n");

  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);

  return NULL;
}

int main() {
  pthread_mutex_init(&mutex1, NULL);
  pthread_mutex_init(&mutex2, NULL);

  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, consuemrA, NULL);
  pthread_create(&tid2, NULL, consumerB, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  pthread_mutex_destroy(&mutex1);
  pthread_mutex_destroy(&mutex2);

  pthread_exit(NULL);
  return 0;
}
