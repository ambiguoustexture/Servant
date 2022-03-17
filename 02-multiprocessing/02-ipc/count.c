#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long cnt = 0;

void sig_handler(int signal) {
  printf("counted: %ld in 1 sec\n", cnt);
  exit(0);
}

int main() {
  signal(SIGALRM, sig_handler);
  alarm(1);
  while (1) {
    cnt++;
  }
  return 0;
}
