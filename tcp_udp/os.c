#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
    struct utsname name;
    if (uname(&name))
        exit(-1);
    printf("Hello! Your computer's OS is: ");

#ifdef __linux__
    printf("Linux ");
#elif __unix__
    printf("Unix ");
#elif __APPLE__
    printf("Mac ");
#endif
    printf("%s\n", name.version);

    return 0;
}