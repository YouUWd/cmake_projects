#include <stdio.h>
#include <float.h>

int main() {
  //整型
  printf("char 存储大小 : %lu \n", sizeof(char));
  printf("uchar 存储大小 : %lu \n", sizeof(unsigned char));
  printf("schar 存储大小 : %lu \n", sizeof(signed char));
  printf("int 存储大小 : %lu \n", sizeof(int));
  printf("uint 存储大小 : %lu \n", sizeof(unsigned int));
  printf("short 存储大小 : %lu \n", sizeof(short));
  printf("ushort 存储大小 : %lu \n", sizeof(unsigned short));
  printf("long 存储大小 : %lu \n", sizeof(long));
  printf("ulong 存储大小 : %lu \n", sizeof(unsigned long));
  //浮点型
  printf("float 存储大小 : %lu %E %E\n", sizeof(float), FLT_MIN, FLT_MAX);
  printf("double 存储大小 : %lu\n", sizeof(double));
  printf("long double 存储大小 : %lu\n", sizeof(long double));

  printf("size NONE %d, CRC32 %d\n", sizeof("NONE"), sizeof("CRC32"));
  return 0;
}