#include <stdio.h>
#include <string.h>

int main() {
  FILE *fp = NULL;
  fp = fopen("./test.txt", "w+");
  fprintf(fp, "AB Hello C File!\n");
  fputs("The Second Line!\n", fp);
  fclose(fp);

  fp = fopen("./test.txt", "r");
  int c = fgetc(fp);
  printf("1: %c\n", c);
  c = fgetc(fp);
  printf("2: %c\n", c);

  char buff[128];
  fscanf(fp, "%s", buff);
  printf("3: %s\n", buff);

  rewind(fp);//重新开始
  fgets(buff, 128, fp);
  printf("1: %s", buff);

  fgets(buff, 128, fp);
  printf("2: %s", buff);

  printf("================\n");
  rewind(fp);

  fread(buff, 16, 8, fp);
  printf("%s", buff);

  printf("================\n");
  printf("================\n");
  rewind(fp);
  while (!feof(fp)) {
    char fb[16];
    memset(fb, 0, sizeof(fb));
    int i = fread(fb, 2, 1, fp);
    int eof = feof(fp);

    printf("<%d %d>", i, eof);
    printf("%s", fb);
  }
  printf("================\n");
  printf("================\n");
  rewind(fp);
  while (!feof(fp)) {
    // 清空缓冲区
    memset(buff, 0, sizeof(buff));
    int i = fread(buff, sizeof(char), 1, fp);
    int eof = feof(fp);
    printf("<%d %d>", i, eof);
    printf("%s", buff);
  }

  fclose(fp);
}
