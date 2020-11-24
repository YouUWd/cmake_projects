#include <stdio.h>
/**
 * 任何一种编程中，作用域是程序中定义的变量所存在的区域，超过该区域变量就不能被访问。C 语言中有三个地方可以声明变量：
1、在函数或块内部的局部变量
2、在所有函数外部的全局变量
3、在形式参数的函数参数定义中
 */

/* 全局变量声明 */
int g;
/* 全局变量声明 */
int a = 30;
int n = 30;
int add(int a, int b) {
  a++;
  return a + b;
}
int main() {
  /* 局部变量声明 */
  int a, b;
  int c;

  /* 实际初始化 */
  a = 10;
  b = 20;
  c = a + b;

  printf("value of a = %d, b = %d and c = %d\n", a, b, c);

  /**
   * 全局变量是定义在函数外部，通常是在程序的顶部。全局变量在整个程序生命周期内都是有效的，在任意的函数内部能访问全局变量。
     全局变量可以被任何函数访问。也就是说，全局变量在声明后整个程序中都是可用的。
   */
  g = a + b;
  printf("value of a = %d, b = %d and g = %d\n", a, b, g);

  int g = 10;
  //在程序中，局部变量和全局变量的名称可以相同，但是在函数内，如果两个名字相同，会使用局部变量值，全局变量不会被使用。
  printf("value of a = %d, b = %d and g = %d\n", a, b, g);

  int add(int, int);

  int s = add(a, b);
  printf("value of a = %d, b = %d and s = %d\n", a, b, s);

  s = add(n, b);
  printf("value of n = %d, b = %d and s = %d\n", n, b, s);
  return 0;
}