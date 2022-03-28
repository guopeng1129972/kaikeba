// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>
#include <math.h>
// #define pi acos(-1)
#define f 1.8
#define C 32

int main()
{
  double c;
  scanf("%lf", &c);
  printf("%.2lf\n", f * c + C);
  return 0;
}