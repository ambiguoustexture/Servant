#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
  // init
  int shmid = shmget(100, 0, IPC_CREAT);
  void *ptr = shmat(shmid, NULL, 0);

  printf("shmid: %d\n", shmid);

  printf("read from shared memory: %s\n", (char *)ptr);

  printf("press any key to continue...\n");
  getchar();

  // de
  shmdt(ptr);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}
