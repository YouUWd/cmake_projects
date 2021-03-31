#include <stdio.h>
#include <string.h>
/**
 * 共用体是一种特殊的数据类型，允许您在相同的内存位置存储不同的数据类型。
 * 您可以定义一个带有多成员的共用体，但是任何时候只能有一个成员带有值。
 * 共用体提供了一种使用相同的内存位置的有效方式。
 */
union Data {
  int id;
  char name[8];
} data;

int main(void) {
  union Data data;
  printf("Memory size occupied by data : %d\n", sizeof(data));
  data.id = 1;
  strcpy(data.name, "Jack");
  printf("data.id : %d\n", data.id);
  printf("data.name : %s\n", data.name);

  data.id = 2;
  printf("data.id : %d\n", data.id);
  strcpy(data.name, "Tim");
  printf("data.name : %s\n", data.name);
  return 0;
}

