// float 4
// double 8  优先推荐定义变量
// int 32b 4B
// 使用定义函数 reverse_num() 方法实现
#include <stdio.h>
#include <string.h>

int reverse_num(int n)
{
  int sum = 0, temp = n;
  while (temp)
  {
    sum = sum * 10 + temp % 10;
    temp /= 10;
  }
  return sum;
}

int main()
{
  // int 2的31次方 个
  int n;
  while (~scanf("%d", &n))
  {
    printf("%d\n", reverse_num(n));
  }
  return 0;
}