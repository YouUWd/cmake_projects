#include <stdio.h>

void f1(int *p) {
  printf("%d \n", p[1]);

  printf("%d %d \n", sizeof(p), sizeof(int));
}

void f2(int p[3]) {
  printf("%d \n", p[1]);
}
void f3(int p[]) {
  printf("%d \n", p[1]);
}

void f4(int p[]) {
  printf("size in f4 = %i \n", sizeof(p));
  printf("size in f4 = %i \n", sizeof(&p));
  printf("size in f4 = %i \n", sizeof(*p));
  printf("%d %d \n", sizeof(p), sizeof(int));
}

void length(int array[]) {
  printf("length = %i \n", array);
  printf("length = %i \n", *array);
}

int main() {
  int a[] = {1, 3, 5};// same as -> int a[3] = {1, 2, 3}

  printf("a[0] = %i \n", a[0]);
  printf("size = %i \n", sizeof(a));

  int b[10];

  for (int kI = 0; kI < 10; ++kI) {
    b[kI] = kI + 1;
  }

  for (int kJ = 0; kJ < 10; ++kJ) {
    printf("%i \n", b[kJ]);
  }

  int c[3][4] = {
      {0, 1, 2, 3},   /*  初始化索引号为 0 的行 */
      {4, 5, 6, 7},   /*  初始化索引号为 1 的行 */
      {8, 9, 10, 11}   /*  初始化索引号为 2 的行 */
  };
  //same as below
  //int a[3][4] = {0,1,2,3, 4,5,6,7,  8,9,10,11};

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("c[%d][%d] = %d \n", i, j, c[i][j]);
    }
  }
  f1(&a);
  f2(a);
  f2(b);
  f3(a);

  printf("size = %i \n", sizeof(a));
  f4(a);

  printf("address %i \n", &a);
  printf("a %i \n", a);
  printf("*a %i \n", *a);
  printf("*(a+1) %i \n", *(a + 1));
  printf("*a+1 %i \n", *a + 1);
  length(a);

  return 0;
}