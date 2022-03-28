// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>
#include <math.h>
// #define pi acos(-1)
#define pi 3.14

int main()
{
  double r;
  scanf("%lf", &r);
  printf("%.2lf\n", 2 * pi * r);
  printf("%.2lf\n", pi * r * r);
  return 0;
}