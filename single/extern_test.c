#include <stdio.h>
#include "include/extern_declare.c"

int x = 1;
int y = 2;
int z = 3;

int add2();

int main(void) {
    int result = add2();
    printf("%d %d %d %d", x, y, z, result);
    return 0;
}
