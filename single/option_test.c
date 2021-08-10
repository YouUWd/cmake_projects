#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int i, j, k;
static const struct option long_options[] = {
    {"im", no_argument, &i, 1},
    {"jm", no_argument, &j, 2},
    {"km", required_argument, NULL, 'k'},
    {NULL, 0, NULL, 0}
};

int main(int argc, char *argv[]) {

  int opt;
  int options_index = 0;
  while ((opt = getopt_long(argc, argv, "ijk:", long_options, &options_index)) != EOF) {

    switch (opt) {
      case 'i':
      case 'j':break;

      case 'k':k = atoi(optarg);
        break;
      default:break;
    }
    printf("%c\n", opt);
    printf("%d\n", opt);

  }
  printf("%d,%d,%d\n", i, j, k);

  return 0;
}