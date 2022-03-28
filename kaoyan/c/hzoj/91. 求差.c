// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>

int main()
{
  int a, b;
  scanf("%d%d", &a, &b);
  printf("%d\n", a - b);
  return 0;
}