#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
extern int errno;

int main() {
  FILE *pf;
  int errnum;
  pf = fopen("unexist.txt", "rb");
  if (pf == NULL) {
    errnum = errno;
    fprintf(stderr, "错误号: %d\n", errno);
    perror("通过 perror 输出错误信息");
    fprintf(stderr, "错误信息: %s\n", strerror(errnum));
    exit(EXIT_FAILURE);
  } else {
    fclose(pf);
  }
  exit(EXIT_SUCCESS);
}