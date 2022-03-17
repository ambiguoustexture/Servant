/*
 * The alarm() function sets a timer
 * to deliver the signal SIGALRM to the calling process
 * after the specified number of seconds.
 * If an alarm has already been set with alarm()
 * but has not been delivered,
 * another call to alarm() will supersede the prior call.
 * The request alarm(0) voids the current alarm
 * and the signal SIGALRM will not be delivered.
 */

#include <stdio.h>
#include <unistd.h>

int main() {
  int seconds = alarm(5);
  printf("seconds = %d\n", seconds); // 0

  sleep(2);
  seconds = alarm(2);                // non-block
  printf("seconds = %d\n", seconds); // 3

  while (1) {
  }

  return 0;
}
