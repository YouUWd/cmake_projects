#include <stdio.h>

int main() {
  int i;
  printf("%d \n", i);
  while (i < 10) {
    i++;
  }
  printf("%d \n", i);
  for (int kI = 0; kI < 10; ++kI) {
    printf("kI = %d \n", kI);
  }

  printf("=======================\n");

  for (int jI = 0; jI < 10; jI++) {
    printf("jI = %d \n", jI);
  }

  int j = 0, k = 0;
  printf("++j=%d \n", ++j);
  printf("k++=%d \n", k++);

  int a = 5;
  int b = ++a;
  printf("a=%d, b=%d\n", a, b);
  int c = a++;
  printf("a=%d, b=%d, c=%d\n", a, b, c);

  int m, n;

  for (m = 0; m <= 3; m++)
    printf(" > iteration #%d", m);

  printf("\n");

  for (n = 0; n <= 3; ++n)
    printf(" > iteration #%d", n);

  return 0;
}
