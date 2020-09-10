#include <stdlib.h>
#include <stdio.h>

/* 函数声明 */
int max(int, int);
/* 函数实现 */
int max(int a, int b) {
  return a > b ? a : b;
}

//传值调用
void swapValue(int a, int b) {
  int temp;
  temp = a;
  a = b;
  b = temp;
}

void swapRefer(int *a, int *b) {
  int temp;
  temp = *a;/* 保存地址 a 的值 */
  *a = *b;  /* 把 b 赋值给 a, a的地址指向b的地址 */
  *b = temp;/* 把 temp 赋值给 b, b的地址指向a的临时地址 */
}

void main() {
  int a = 100, b = 200;
  printf("%d \n", max(a, b));

  printf("%i, %i\n", a, b);
  swapValue(a, b);
  printf("%i, %i\n", a, b);
  /**
    * &a 表示指向 a 的指针，即变量 a 的地址
    * &b 表示指向 b 的指针，即变量 b 的地址
   **/
  swapRefer(&a, &b);
  printf("%i, %i\n", a, b);
  exit(0);// same as return 0;
}