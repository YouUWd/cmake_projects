#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char name[100];
  char *description;
  strcpy(name, "Kate");
  //  malloc(size)返回内存中至少可以使用size字节的位置。您可能可以在s[size]之后立即写入字节，【但是】：
  //  这些字节可能属于程序的其他位，这将在以后的执行中导致问题。
  description = (char *) malloc(16 * sizeof(char));//不初始化
  // 等同于以下语句
  //  description = (char *) calloc(16, sizeof(char));//初始化每个字节均为0

  if (description == NULL) {
    printf(stderr, "Error - unable to allocate required memory\n");
  } else {
    strcpy(description, "Kate is 10 years old! ");
  }
  printf("Name: %s, Description: %s\n", name, description);

  /* 假设您想要存储更大的描述信息,在此之前，不能free */

  description = (char *) realloc(description, 128 * sizeof(char));
  if (description == NULL) {
    fprintf(stderr, "Error - unable to allocate required memory\n");
  } else {
    strcat(description, "She is very smart!");
  }
  printf("Name: %s, Description: %s\n", name, description);
  free(description);
  description = NULL;
}
