#include <stdio.h>

int main() {
  long int binary, remainder;

  printf("Enter the binary number: ");
  scanf("%ld", &binary);
  while (binary != 0) {
    int rt = 0;
    for (int i = 0; i < 4 && binary != 0; ++i) {
      remainder = binary % 10;
      binary = binary / 10;
      rt += (remainder << i);
    }
    printf("The equivalent hexadecimal value: %lX\n", rt);
  }

  return 0;
}
