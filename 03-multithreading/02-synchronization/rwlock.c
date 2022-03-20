#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int rec = 1;

pthread_rwlock_t rwlock;

void *writer(void *arg) {
  while (1) {
    pthread_rwlock_wrlock(&rwlock);
    printf("writer: %ld writed: %d\n", pthread_self(), ++rec);
    pthread_rwlock_unlock(&rwlock);
    usleep(100);
  }

  return NULL;
}

void *reader(void *arg) {
  while (1) {
    pthread_rwlock_rdlock(&rwlock);
    printf("reader: %ld read:   %d\n", pthread_self(), rec);
    pthread_rwlock_unlock(&rwlock);
    usleep(100);
  }

  return NULL;
}

int main() {

  pthread_rwlock_init(&rwlock, NULL);
  pthread_t wtids[3], rtids[5];
  for (int i = 0; i < 3; i++) {
    pthread_create(&wtids[i], NULL, writer, NULL);
  }

  for (int i = 0; i < 5; i++) {
    pthread_create(&rtids[i], NULL, reader, NULL);
  }

  for (int i = 0; i < 3; i++) {
    pthread_detach(wtids[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_detach(rtids[i]);
  }

  pthread_exit(NULL);

  printf("after detachment\n");
  pthread_rwlock_destroy(&rwlock);

  return 0;
}
