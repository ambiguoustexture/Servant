#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid > 0) {
    // parrent process: sending
    if (access("fifo2", F_OK) == -1) {
      printf("prepare for sending...\n");
      if (mkfifo("fifo2", 0664) == -1) {
        perror("mkfifo");
        // exit(0);
      }
    }

    char msg_w[144];
    while (1) {
      int fd_s = open("fifo2", O_WRONLY);
      if (fd_s == -1) {
        perror("open");
        // exit(0);
      }

      memset(msg_w, 0, sizeof(msg_w));
      printf("> ");
      fgets(msg_w, sizeof(msg_w), stdin);
      if (write(fd_s, msg_w, sizeof(msg_w)) == -1) {
        perror("send message failed:(\n");
        // exit(1);
      }
    }
  } else if (pid == 0) {
    // child  process: reading
    if (access("fifo1", F_OK) == -1) {
      printf("prapare for reciving...\n");
      if (mkfifo("fifo1", 0664) == -1) {
        perror("mkfifo");
        // exit(0);
      }
    }

    char msg_r[144];
    while (1) {
      int fd_r = open("fifo1", O_RDONLY);
      if (fd_r == -1) {
        perror("open");
        // exit(0);
      }

      memset(msg_r, 0, sizeof(msg_r));
      if (read(fd_r, msg_r, sizeof(msg_r)) == -1) {
        perror("read message failed:(");
        // exit(1);
      }
      printf("\n< %s", msg_r);
    }
  }
}
