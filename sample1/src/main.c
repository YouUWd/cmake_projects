#include <stdio.h>
#include "../include/hello.h"

int main() {
    printf("Hello, World!\n");
    printf("%d \n", LEN_32);
    int ret = add(LEN_32, 20);
    printf("%d \n", ret);
    return 0;
}