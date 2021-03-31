#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc == 2) {
    printf("The argument count is %d, supplied is %s\n", argc, argv[1]);
  } else if (argc > 2) {
    printf("The argument supplied is %d, ", argc);
    for (int i = 0; i < argc - 1; i++) {
      printf("%s ", argv[i + 1]);
    }
    printf("\n");
  } else {
    printf("argument expected.\n");
  }

}