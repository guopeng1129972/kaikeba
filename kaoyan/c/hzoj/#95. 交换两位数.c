// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>
#include <string.h>

int main()
{
  // int 2的31次方 个
  int n;
  scanf("%d", &n);
  printf("%d%d\n", n % 10, n / 10);
  return 0;
}