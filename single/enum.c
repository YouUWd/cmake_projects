#include <stdio.h>

#define E_MON  1
#define E_TUE  2
#define E_WED  3
#define E_THU  4
#define E_FRI  5
#define E_SAT  6
#define E_SUN  7

enum DAY {
  MON = 1, TUE = 3, WED, THU, FRI, SAT, SUN
} day;

int main() {

  printf("%d \n", E_MON);
  printf("%d \n", MON);
  printf("%d \n", TUE);
  enum DAY d = SUN;
  printf("%d \n", d);

  printf("=====================\n");
  for (day = MON; day <= SUN; day++) {
    printf("%d \n", day);
  }
  printf("=====================\n");

  int a = 3;
  printf("a = %d \n", &a);
  enum DAY wed = a;
  printf("w = %d \n", &wed);
  printf("wed = %d \n", wed);

  return 0;
}
