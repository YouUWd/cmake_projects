#include <stdio.h>

void main() {
  int i;
  printf("%d \n", i);
  if (i) {
    i++;
  } else {
    i--;
  }
  printf("%d \n", i);

  while (i) {
    if (i < 0)
      i++;
    if (i > 0)
      i--;
  }
  printf("%d \n", i);

  i++;
  switch (i) {
    case 0:i++;
      break;
    case 1:i--;
      break;
    default:break;
  }

  printf("%d \n", i);

}
