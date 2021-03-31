#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char BYTE;
int main() {

  BYTE b1, b2;
  b1 = 1;
  b2 = 2;

  printf("%d %d\n", b1, b2);

  printf("TRUE 的值: %d\n", TRUE);
  printf("FALSE 的值: %d\n", FALSE);

  return 0;
}