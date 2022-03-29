// float 4
// double 8  优先推荐定义变量
// int 32b 4B
// scanf("%lf", &gongZi); //读入一个浮点数
#include <stdio.h>
#include <math.h>
#define lilv 0.00417

int main()
{
  double sum = 0;
  int time = 6;
  double gongZi;
  scanf("%lf", &gongZi);
  while (time--)
  {
    sum = (sum + gongZi) * (lilv + 1);
  }
  printf("$%.2lf\n", sum);
  return 0;
}