#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//int    *ip;    /* 一个整型的指针 */
//double *dp;    /* 一个 double 型的指针 */
//float  *fp;    /* 一个浮点型的指针 */
//char   *ch;     /* 一个字符型的指针 */

void f1(int a) {
  a = 10;
}

void f2(int *a) {
  *a = 20;
}

int *f3() {
  static int r[10];
  int i;

  /* 设置种子 */
  srand((unsigned) time(NULL));
  for (i = 0; i < 10; ++i) {
    r[i] = rand();
//    printf("%d\n", r[i]);
  }

  return r;
}

int main() {
  int var = 20;
  int *p_int = &var;
  printf("%d %d \n", var, *p_int);
  printf("%d %d \n", var, *(p_int + 1));
  printf("%d %d \n", var, *(p_int - 1));

  //same as below
  printf("%d %d \n", var, p_int[0]);
  printf("%d %d \n", var, p_int[1]);
  printf("%d %d \n", var, p_int[-1]);

  printf("====================\n");
  int a = NULL;
  int *b = &a;
  int *p = NULL;
  printf("%d %d %d %d\n", &a, *b, b, p);
  if (!a) {
    printf("a is null \n");
  }

  if (!p) {
    printf("*p is null \n");
  }
  printf("====================\n");
  //  指针的每一次递增，它其实会指向下一个元素的存储单元。
  //  指针的每一次递减，它都会指向前一个元素的存储单元。
  //  指针在递增和递减时跳跃的字节数取决于指针所指向变量数据类型长度，比如 int 就是 4 个字节。
  int ar[] = {1, 3, 5};
  int i, *pt;
  pt = ar;
  for (int i = 0; i < 3; ++i) {
    printf("%d %d %d %d\n", ar[i], &ar[i], pt, *pt);
    pt++;
  }

  printf("====================\n");

  char c[] = {'a', 'c', 'e'};
  char *p_c;
  p_c = c;

  while (p_c <= &c[2]) {
    printf("%d %d %c\n", p_c, &c[2], *p_c);
    p_c++;
  }

  printf("====================\n");

  int *ptr;
  int **pptr;

  var = 3000;

  /* 获取 var 的地址 */
  ptr = &var;

  /* 使用运算符 & 获取 ptr 的地址 */
  pptr = &ptr;

  /* 使用 pptr 获取值 */
  printf("Value of var = %d\n", var);
  printf("Value available at *ptr = %d\n", *ptr);
  printf("Value available at **pptr = %d %d %d %d\n", **pptr, ptr, pptr, *pptr);

  printf("====================\n");

  printf("%d \n", a);
  f1(a);
  printf("%d \n", a);
  f2(&a);
  printf("%d \n", a);

  printf("====================\n");
  p = f3();
  printf("%d \n", *p);

}