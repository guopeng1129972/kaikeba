// 实现读入2个整数k,b;输出y=k*x+b直线方程中x=1到x=100间y的值
#include <stdio.h>
int fun(int x, int k, int b)
{
  return k * x + b;
}
int main()
{
  int k, b;
  scanf("%d%d", &k, &b);
  for (int i = 1; i < 101; i++)
  {
    printf("%d\n", fun(i, k, b));
  }
  return 0;
}