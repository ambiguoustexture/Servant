#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void sig_handler(int signal) {
  printf("recv signal: %d\n", signal);
}

int main() {
  signal(SIGALRM, sig_handler);
  struct itimerval new_value; {
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;
  }

  printf("countdown started...\n");
  if (setitimer(ITIMER_REAL, &new_value, NULL) == -1) { // non-block
    perror("setitimer");
    exit(0);
  }

  getchar();

  return 0;
}
