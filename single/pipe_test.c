/**
 *
  https://www.geeksforgeeks.org/pipe-system-call/
  int pipe(int fds[2]);
  Parameters :
  fd[0] will be the fd(file descriptor) for the
  read end of pipe.
  fd[1] will be the fd for the write end of pipe.
  Returns : 0 on Success.
  -1 on error.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16
char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

void write_read_single();
void write_read_fork();
int main() {
//  write_read_single();

  printf("Main[%d - %d]\n", getppid(), getpid());
  write_read_fork();

  return 0;
}
void write_read_single() {
  char inbuf[MSGSIZE];
  int p[2], i;
  if (pipe(p) < 0)
    exit(EXIT_FAILURE);
  /* continued */
  /* write pipe */
  write(p[1], msg1, MSGSIZE);
  write(p[1], msg2, MSGSIZE);
  write(p[1], msg3, MSGSIZE);

  for (i = 0; i < 3; i++) {
    /* read pipe */
    read(p[0], inbuf, MSGSIZE);
    printf("% s\n", inbuf);
  }
}

void write_read_fork() {
  printf("Method [%d - %d]\n", getppid(), getpid());
  char inbuf[MSGSIZE];
  int p[2], i;
  if (pipe(p) < 0)
    exit(EXIT_FAILURE);

  pid_t pid = fork();

  if (pid == 0) {//child
    printf("Write [%d - %d] %d\n", getppid(), getpid(), pid);
    /* continued */
    /* write pipe */
    write(p[1], msg1, MSGSIZE);
    sleep(5);
    write(p[1], msg2, MSGSIZE);
    sleep(5);
    write(p[1], msg3, MSGSIZE);
  } else {//main
    printf("Read [%d - %d] %d\n", getppid(), getpid(), pid);
    for (i = 0; i < 3; i++) {
      /* read pipe */
      read(p[0], inbuf, MSGSIZE);
      printf("% s\n", inbuf);
    }
  }

  wait(0);

}
