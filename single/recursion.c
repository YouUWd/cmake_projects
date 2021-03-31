#include <stdio.h>

int fib(int i) {
  if (i == 1 || i == 0) {
    return 1;
  } else {
    return fib(i - 1) + fib(i - 2);
  }
}

int main() {
  for (int i = 0; i < 10; i++) {
    printf("%d\t", fib(i));
  }
}

