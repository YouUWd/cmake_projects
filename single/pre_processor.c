/**
 *
#define	定义宏
#include	包含一个源代码文件
#undef	取消已定义的宏
#ifdef	如果宏已经定义，则返回真
#ifndef	如果宏没有定义，则返回真
#if	如果给定条件为真，则编译下面代码
#else	#if 的替代方案
#elif	如果前面的 #if 给定条件不为真，当前条件为真，则编译下面代码
#endif	结束一个 #if……#else 条件编译块
#error	当遇到标准错误时，输出错误消息
#pragma	使用标准化方法，向编译器发布特殊的命令到编译器中
 *
 */

#include <stdio.h>
#include "include/myheader.h"

#ifdef DEBUG
/* Your debugging statements here */
#endif

#ifndef MESSAGE  //等价 if !defined (MESSAGE)
#define MESSAGE "You wish!"
#endif
//在宏定义中，当需要把一个宏的参数转换为字符串常量时，则使用字符串常量化运算符（#）。在宏中使用的该运算符有一个特定的参数或参数列表。
#define  message_for(a, b)  \
    printf(#a " and " #b ": We love you!\n")

//标记粘贴运算符（##）
#define tokenPaster(n) printf ("token" #n " = %d\n", token##n)

//参数化的宏。 参数列表是括在圆括号内，且必须紧跟在宏名称的后边。宏名称和左圆括号之间不允许有空格
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main() {
  printf("%d %s\n", LENGTH, MESSAGE);

  printf("File :%s\n", __FILE__);
  printf("Date :%s\n", __DATE__);
  printf("Time :%s\n", __TIME__);
  printf("Line :%d\n", __LINE__);
  printf("ANSI :%d\n", __STDC__);

  message_for(A, B);

  int token1 = 2;

  tokenPaster(1);

  printf("MAX(1, 2) = %d\n", MAX(1, 2));
  return 0;
}