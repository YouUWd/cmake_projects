#include <stdio.h>

int x, y;

int add() {
  extern int x, y;
  x = 1, y = 2;
  return x + y;
}

int main() {
  int i, j, k = 1;
  printf("%d %d %d\n", i, j, k);
  printf("%d %d %d\n", x, y, add());
  return 0;
}