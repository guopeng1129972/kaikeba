// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>
#include <math.h>
// #define pi acos(-1)
// #define pi 3.14

int add_num(int n)
{
  int sum = 0, temp = n;
  while (temp)
  {
    // 计算逻辑 123 % 10 = 3 sum=0+3
    sum = sum + temp % 10;
    // 取值操作 123 /10 = 12
    temp /= 10;
  }
  return sum;
}

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    printf("%d\n", add_num(n));
  }
  return 0;
}