#include <stdio.h>
#include <unistd.h>
int main() {
  int mypipe[2];
  /* create pipe */
  if (pipe(mypipe)) {
    perror("pipe failed.");
    return 3;
  }
  /* write results to pipe */
  FILE *f = fdopen(mypipe[1], "w");
  if (f == NULL) {
    perror("open pipe for writing failed.");
    return 3;
  }
  /* fprintf(stderr,"Child - %d %d\n",speed,failed); */
  fprintf(f, "%d %d %d\n", 1, 2, 3);
  fclose(f);

  /* read results from pipe */
  f = fdopen(mypipe[0], "r");
  if (f == NULL) {
    perror("open pipe for reading failed.");
    return 3;
  }
  setvbuf(f, NULL, _IONBF, 0);
  int i, j, k;
  pid_t pid = fscanf(f, "%d %d %d", &i, &j, &k);

  printf("pid=%d, i=%d, j=%d, k=%d", pid, i, j, k);
  return 0;
}