
/*
 * int sigemptyset(sigset_t *set);
 *
 * int sigfillset(sigset_t *set);
 *
 * int sigaddset(sigset_t *set, int signum);
 *
 * int sigdelset(sigset_t *set, int signum);
 *
 * int sigismember(const sigset_t *set, int signum);
 */

#include <signal.h>
#include <stdio.h>

int main() {
  sigset_t set;
  sigemptyset(&set);

  int ret = sigismember(&set, SIGINT);
  if (ret == 0) {
    printf("SIGINT  not found in set\n");
  } else if (ret == 1) {
    printf("SIGINT  existed\n");
  }

  printf("add SIGINT  & SIGQUIT to set\n");
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGQUIT);

  ret = sigismember(&set, SIGINT);
  if (ret == 0) {
    printf("SIGINT  not found in set\n");
  } else if (ret == 1) {
    printf("SIGINT  found\n");
  }

  ret = sigismember(&set, SIGQUIT);
  if (ret == 0) {
    printf("SIGQUIT not found in set\n");
  } else if (ret == 1) {
    printf("SIGQUIT found\n");
  }

  printf("del SIGQUIT\n");
  sigdelset(&set, SIGQUIT);

  ret = sigismember(&set, SIGQUIT);
  if (ret == 0) {
    printf("SIGQUIT not found in set\n");
  } else if (ret == 1) {
    printf("SIGQUIT found\n");
  }

  return 0;
}
