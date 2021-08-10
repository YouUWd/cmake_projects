#include <stdio.h>

int main() {
  int input;
  printf("Enter the binary number: ");

  scanf("%d", &input);

  printf("input entered %d\n", input);

  int i = 0, result = 0;
  while (input > 0) {
    int low = input % 10;
    input = input / 10;
    result += (low << i);
    i++;
  }
  printf("num result %d\n", result);
  printf("hex result %x\n", result);
  return 0;
}
