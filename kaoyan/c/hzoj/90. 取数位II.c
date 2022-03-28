// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>

int main()
{
  int a;
  scanf("%d", &a);
  printf("%d\n", a / 100);
  printf("%d\n", (a - (a / 100) * 100) / 10);
  printf("%d\n", (a - (a / 100) * 100) % 10);
  return 0;
}