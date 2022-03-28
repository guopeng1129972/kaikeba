#include <stdio.h>
#include <math.h>
// 计算一个数x的立方根
int main()
{
  double x;
  while (~scanf("%lf", &x))
  {
    printf("%lf\n", pow(x, 1.0 / 3.0));
  }
  return 0;
}