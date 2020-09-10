#include <stdio.h>
#define VERSION "1.0.1"
#define NUMBER 1
int main() {
  printf("%s\n", VERSION);
  printf("%d\n", NUMBER);

  const int NUMBER_N = 2;
  printf("%d\n", NUMBER_N);

  return 0;
}
