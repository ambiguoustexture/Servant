#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void sighandler(int signal) { printf("signal: %d captured\n", signal); }

int main() {
  struct sigaction act;
  act.sa_flags = 0;
  act.sa_handler = sighandler;
  sigemptyset(&act.sa_mask);

  sigaction(SIGALRM, &act, NULL);

  struct itimerval new_value;
  {
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;
  }

  printf("timing...\n");
  if (setitimer(ITIMER_REAL, &new_value, NULL) == -1) {
    perror("setitimer");
    exit(0);
  }

  while (1)
    ;

  return 0;
}
