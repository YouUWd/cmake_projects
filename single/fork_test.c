#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void m();
void m0();
void m1();
void m2();
/**
 * https://www.geeksforgeeks.org/fork-system-call/
 */
int main() {
  m2();
}

void m() {
  printf("Main[%d - %d]\n", getppid(), getpid());
  printf("[%d - %d] 1 \n", getppid(), getpid());
  pid_t pid = 0;
  printf("[%d - %d] 2 %d\n", getppid(), getpid(), pid);
  pid = fork();
  printf("[%d - %d] 3 %d\n", getppid(), getpid(), pid);

  pid = fork();
  printf("[%d - %d] 4 %d\n", getppid(), getpid(), pid);

  wait(0);
}

void m0() {
  printf("Main[%d - %d]\n", getppid(), getpid());
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

void m1() {
  printf("Main[%d - %d]\n", getppid(), getpid());
  pid_t pid = 0;
  for (int i = 0; i < 2; i++) {
    pid = fork();
  }

  if (pid == (pid_t) 0) {
    printf("[%d - %d] %d 1Fork\n", getppid(), getpid(), pid);
  } else {
    printf("[%d - %d] %d 2Fork\n", getppid(), getpid(), pid);
  }
  wait(0);
}

void m2() {
  printf("Main[%d - %d]\n", getppid(), getpid());
  printf("[%d - %d] 1 \n", getppid(), getpid());
  pid_t pid = 0;

  for (int i = 'A'; i < 'C'; ++i) {
    pid = fork();
    printf("[%d - %d] 2 pid=%d %c\n", getppid(), getpid(), pid, i);
    if (pid <= 0) {//阻止fork进程继续fork
      sleep(1);
      break;
    }
  }
  printf("[%d - %d] 3 pid=%d\n", getppid(), getpid(), pid);

  wait(0);
}

