#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
  // init
  int shmid = shmget(100, 4096, IPC_CREAT | 0664);
  void *shmptr = shmat(shmid, NULL, 0);

  printf("shmid: %d\n", shmid);

  const char *str = "data writed to shared memroy";
  memcpy(shmptr, str, strlen(str) + 1);

  printf("press any key to continue\n");
  getchar();

  // de
  shmdt(shmptr);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}
