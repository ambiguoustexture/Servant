#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void sighandler(int num) {
  time_t tm = time(NULL);
  struct tm *loc = localtime(&tm);

  char *str = asctime(loc);
  int fd = open("demod.log", O_RDWR | O_CREAT | O_APPEND, 0664);
  write(fd, str, strlen(str));
  close(fd);
}

int main() {
  // 1. Call umask to set the file mode creation mask to a known value, usually
  // 0.
  umask(0);

  // 2. Call fork and have the parent exit. This does several things. First, if
  // the daemon was started as a simple shell command, having the parent
  // terminate makes the shell think that the command is done. Second, the child
  // inherits the process group ID of the parent but gets a new process ID, so
  // we’re guaranteed that the child is not a process group leader. This is a
  // prerequisite for the call to setsid that is done next.
  pid_t pid = fork();
  if (pid > 0) {
    exit(0);
  }

  // 3. Call setsid to create a new session. The three steps listed in
  // Section 9.5 occur. The process (a) becomes the leader of a new session, (b)
  // becomes the leader of a new process group, and (c) is disassociated from
  // its controlling terminal.
  setsid();

  // 4. Change the current working directory to the root directory. The current
  // working directory inherited from the parent could be on a mounted file
  // system. Since daemons normally exist until the system is rebooted, if the
  // daemon stays on a mounted file system, that file system cannot be
  // unmounted.
  // chdir("~/");

  // 5. Unneeded file descriptors should be closed. This prevents the daemon
  // from holding open any descriptors that it may have inherited from its
  // parent (which could be a shell or some other process).

  // 6. Some daemons open file descriptors 0, 1, and 2 to /dev/null so that any
  // library routines that try to read from standard input or write to standard
  // output or standard error will have no effect.
  int fd = open("/dev/null", O_RDWR);
  dup2(fd, STDIN_FILENO);
  dup2(fd, STDOUT_FILENO);
  dup2(fd, STDERR_FILENO);

  struct sigaction act;
  {
    act.sa_flags = 0;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);
  }

  struct itimerval val;
  {
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;
  }
  setitimer(ITIMER_REAL, &val, NULL);

  // keep running
  while (1) {
    sleep(10);
  }

  return 0;
}
