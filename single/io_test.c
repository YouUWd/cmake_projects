#include <stdio.h>

int main() {

  char c = getchar();
  printf("Entered: ");
  putchar(c);
  printf("\n================\n");
  char input[4];
//  gets(input);
  printf("%d %d \n", sizeof input, sizeof input[0]);
  fgets(input, (sizeof input / sizeof input[0]), stdin);
  printf("Entered: ");
  puts(input);
  printf("\n================\n");

  int i;
  char s[4];
  scanf("%d %s", &i, s);
  printf("%d %s\n", i, s);
  return 0;
}