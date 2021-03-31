#include <stdio.h>
extern int mount;
void write_extern() {
  printf("mount is %d\n", mount);
}