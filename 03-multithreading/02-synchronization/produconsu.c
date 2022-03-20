#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

struct Item {
  int value;
  struct Item *next;
};

struct Item *head = NULL;

void *producer(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    struct Item *curr = (struct Item *)malloc(sizeof(struct Item));
    curr->next = head;
    head = curr;
    curr->value = rand() % 1000;
    printf("producer: %ld produced: %-3d\n", pthread_self(), curr->value);
    pthread_mutex_unlock(&mutex);
    usleep(100);
  }

  return NULL;
}

void *customer(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    struct Item *curr = head;

    if (head != NULL) {
      head = head->next;
      printf("consumer: %ld consumed: %-3d\n", pthread_self(), curr->value);
      free(curr);
      pthread_mutex_unlock(&mutex);
      usleep(100);
    } else {
      pthread_mutex_unlock(&mutex);
    }
  }
  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t ptids[3], ctids[5];

  for (int i = 0; i < 5; i++) {
    pthread_create(&ptids[i], NULL, producer, NULL);
    pthread_create(&ctids[i], NULL, customer, NULL);
  }

  for (int i = 0; i < 5; i++) {
    pthread_detach(ptids[i]);
    pthread_detach(ctids[i]);
  }

  pthread_mutex_destroy(&mutex);

  pthread_exit(NULL);

  return 0;
}
