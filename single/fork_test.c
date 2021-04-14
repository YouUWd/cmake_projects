#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  printf("[%d - %d]Main\n", getppid(), getpid());
  for (int i = 0; i < 3; i++) {
//    printf("i - %d\n", i);
    int pid = fork();
    printf("[%d - %d] pid =%d - %d\n", getppid(), getpid(), pid, i);
    _exit(pid);
  }

//  fork();
//  fork() && fork() || fork();
//  fork();
//
//  printf("forked\n");
  wait(0);
}

