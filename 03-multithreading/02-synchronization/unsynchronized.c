#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int items = 144;

void *consume(void *arg) {
  while (items > 0) {
    usleep(2022);
    printf("thread: %ld is consumeing the %-5d item\n", pthread_self(),
           items--);
  }
  return NULL;
}

int main() {
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

  pthread_exit(NULL);

  return 0;
}
