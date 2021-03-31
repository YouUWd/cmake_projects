#include <stdio.h>
#include <stdarg.h>

double avg(int size, ...) {
  va_list list;
  double sum = 0.0;
  va_start(list, size);
  for (int i = 0; i < size; ++i) {
    sum += va_arg(list, int);
  }

  va_end(list);
  return sum / size;
}

int main() {
  printf("%f\n", avg(2, 1, 2));
  printf("%f\n", avg(2, 2, 3));
  printf("%f\n", avg(2, 3, 4));
}
