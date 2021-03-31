#include <stdio.h>

int main() {
  int sum = 10, count = 3;
  //强制类型转换运算符的优先级大于除法，因此 sum 的值首先被转换为 double 型，然后除以 count，得到一个类型为 double 的值
  double mean = (double) sum / count;
  printf("Value of mean : %f\n", mean);

  //整数提升
  /**
   * 隐式转换可能会丢失信息，符号可能会丢失，并且可能发生溢出（当long long被隐式转换为float时)
   * bool - > char - > short int - > int - > unsigned int - > long - > unsigned - > long long - > float - > double - > long double
   */
  int i = 17;
  char c = 'c'; /* ascii 值是 99 */
  sum = i + c;
  printf("Value of sum : %d\n", sum);

  int a = 17;
  char b = 'c'; /* ascii 值是 99 */
  float f;

  f = a + b;// a 和 b 先各自转float, 转换的结果也会保存到临时的内存空间，不会改变数据本来的类型或者值
  printf("Value of a : %d %f\n", a, a);
  printf("Value of b : %d %f\n", b, b);
  printf("Value of sum : %f\n", f);

  int ic = 99;
  char cc = ic;

  printf("Value of cc : %c\n", cc);

}