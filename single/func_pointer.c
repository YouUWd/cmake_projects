#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
  return x > y ? x : y;
}

int init(int *arr, int size, int (*nv(void))) {
  for (int i = 0; i < size; ++i) {
    arr[i] = nv();
  }
}

int next(void) {
  int r = rand();
  return r;
}

int main(void) {

  int (*p)(int, int) = &max;
  int m = p(p(1, 2), 3);
  printf("Max %d \n", m);

  int a[10];
  init(a, 10, &next);
  for (int i = 0; i < 10; ++i) {
    printf("a[%d]=%d \n", i, a[i]);
  }
}