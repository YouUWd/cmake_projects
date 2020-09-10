#include <stdio.h>
#include "support.c"
int mount;
//auto int month; //auto 只能用在函数内，即 auto 只能修饰局部变量

static int count = 10;        /* 全局变量 - static 是默认的 */


void f1(void) {
/* 'thingy' 是 'f1' 的局部变量 - 只初始化一次
 * 每次调用函数 'f1' 'thingy' 值不会被重置。
 */
  static int thingy = 0;
  thingy++;
  printf(" thingy 为 %d ， count 为 %d\n", thingy, count);
}

int main() {
  mount = 20;
  auto int month;

  //register 存储类用于定义存储在寄存器中而不是 RAM 中的局部变量。
  // 这意味着变量的最大尺寸等于寄存器的大小（通常是一个词），且不能对它应用一元的 '&' 运算符（因为它没有内存位置）
  register int miles;
  printf(" %d \n", count);
  while (count--) {
    f1();
  }
  write_extern();

  printf(" %d \n", mount++);
  printf(" %d \n", mount);
  printf(" %d \n", ++mount);
}
