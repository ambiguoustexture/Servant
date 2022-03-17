#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sighandler(int signal) {
  printf("signal：%d captured\n", signal);
  while (1) {
    int ret = waitpid(-1, NULL, WNOHANG);
    if (ret > 0) {
      printf("child  process: %d died\n", ret);
    } else if (ret == 0) {
      break;
    } else if (ret == -1) {
      break;
    }
  }
}

int main() {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGCHLD);
  sigprocmask(SIG_BLOCK, &set, NULL);

  pid_t pid;
  for (int i = 0; i < 10; i++) {
    pid = fork();
    if (pid == 0) {
      break;
    }
  }

  if (pid > 0) {
    // parent process
    struct sigaction act;
    {
      act.sa_flags = 0;
      act.sa_handler = sighandler;
      sigemptyset(&act.sa_mask);
      sigaction(SIGCHLD, &act, NULL);
    }
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    while (1) {
      printf("parent process: %d\n", getpid());
      sleep(2);
    }
  } else if (pid == 0) {
    printf("child  process: %d\n", getpid());
  }

  return 0;
}
