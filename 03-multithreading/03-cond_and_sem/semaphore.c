#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

sem_t sem_prod, sem_cons;

struct Item {
  int value;
  struct Item *next;
};

struct Item *head = NULL;

void *producer(void *arg) {
  while (1) {
    sem_wait(&sem_prod);
    pthread_mutex_lock(&mutex);
    struct Item *curr = (struct Item *)malloc(sizeof(struct Item));
    curr->next = head;
    head = curr;
    int produced;
    sem_getvalue(&sem_prod, &produced);
    curr->value = produced;
    printf("producer: %ld produced: %-3d\n", pthread_self(), curr->value);
    pthread_mutex_unlock(&mutex);
    sem_post(&sem_cons);
  }

  return NULL;
}

void *consumer(void *arg) {
  while (1) {
    sem_wait(&sem_cons);
    pthread_mutex_lock(&mutex);
    struct Item *curr = head;

    if (head != NULL) {
      head = head->next;
      printf("consumer: %ld consumed: %-3d\n", pthread_self(), curr->value);
      free(curr);
      pthread_mutex_unlock(&mutex);
      sem_post(&sem_prod);
    } else {
      pthread_mutex_unlock(&mutex);
      sem_post(&sem_prod);
    }
  }
  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  sem_init(&sem_prod, 0, 8);
  sem_init(&sem_cons, 0, 0);
  pthread_t ptids[3], ctids[5];

  for (int i = 0; i < 5; i++) {
    pthread_create(&ptids[i], NULL, producer, NULL);
    pthread_create(&ctids[i], NULL, consumer, NULL);
  }

  for (int i = 0; i < 5; i++) {
    pthread_detach(ptids[i]);
    pthread_detach(ctids[i]);
  }
  sem_destroy(&sem_prod);
  sem_destroy(&sem_cons);
  pthread_mutex_destroy(&mutex);

  pthread_exit(NULL);

  return 0;
}
