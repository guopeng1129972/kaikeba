// float 4
// double 8  优先推荐定义变量
// int 32b 4B

// scanf 方法接收 float
// 结果保留2位小数 %.2lf %.xlf

#include <stdio.h>

int main()
{
  double a, b, c;
  scanf("%lf%lf", &a, &b);
  printf("%.2lf\n", (a + b) * 2);
  printf("%.2lf\n", a * b);
  return 0;
}