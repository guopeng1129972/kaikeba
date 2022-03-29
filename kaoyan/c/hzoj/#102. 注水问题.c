// float 4
// double 8  优先推荐定义变量
// int 32b 4B
// scanf("%lf", &gongZi); //读入一个浮点数

#include <stdio.h>

int main()
{
  int a, b, c, t;

  // double sum;
  // scanf("%d%d%d%d", &a, &b, &c, &t);
  //这是数学表示 算出来是整数，但是答案是用的1.0去除 存在误差，感觉我也没不对
  // sum = t + (a * b - t * b - t * a) * c / (b * c + a * c - a * b);
  // printf("%.2lf\n", sum);

  scanf("%d%d%d%d", &a, &b, &c, &t);
  double temp = (1.0 / a + 1.0 / b);
  printf("%.2lf\n", (1 - temp * t) / (temp - 1.0 / c) + t);

  return 0;
}