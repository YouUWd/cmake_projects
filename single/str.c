#include <stdio.h>
#include <string.h>

void charSplit() {
  printf("=============charSplit============\n");
  char buffer[] = {'H', 'E', 'L', 'L', 'O', '\0', 'A', 'B', '\0'};

  char *first;
  char *second;

  first = buffer;
  second = first;

  while (*second != '\0') {
    second++;
  }
  second++;

  printf("%s\n", first);
  printf("%s\n", second);

  printf("%d\n", strcmp(second, "AB"));
}

void sprint() {
  printf("=============sprint============\n");
  char buffer[16];
  sprintf(buffer, "Hello!");
  printf("%s\n", buffer);
}

int main(void) {
  char str1[] = {'H', 'E', 'L', 'L', 'O', '\0'};
  char str2[] = "HELLO";
  printf("str1: %s %d\n", str1, strlen(str1));
  printf("str2: %s %d\n", str2, strlen(str2));

  char str3[16];
  stpcpy(str3, str1);//复制
  printf("str3: %s %d\n", str3, strlen(str3));

  strcat(str3, str2);//连接
  printf("str3: %s %d\n", str3, strlen(str3));

  int c = strcmp(str1, str2);//比较
  printf("str1:(%s) - str2:(%s) = %d\n", str1, str2, c);

  char *idx1 = strchr(str1, 'H');
  printf("find L at %d\n", idx1);
  if (idx1 == NULL) {
    printf("idx is null\n");
  }
  if (idx1 == 0) {
    printf("idx is 0\n");
  }
  printf("find L at idx %d\n", idx1 - str1);

  char *idx2 = strchr(str1, 'A');
  printf("find A at %d\n", idx2);
  if (idx2 == NULL) {
    printf("idx is null\n");
  }
  if (idx2 == 0) {
    printf("idx is 0\n");
  }
  printf("find A at idx %d\n", idx2 - str1);

  char *idx3 = strstr(str1, "LO");
  printf("find HO at idx %d\n", idx3 - str1);

  char *idx4 = strrchr(str1, 'L');
  printf("find L from right at idx %d\n", idx4 - str1);

  charSplit();
  sprint();
  return 0;
}
