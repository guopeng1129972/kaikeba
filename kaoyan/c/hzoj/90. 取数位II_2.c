// float 4
// double 8  优先推荐定义变量
// int 32b 4B

#include <stdio.h>
#include <string.h>

int main()
{
  // int 2的31次方 个
  char str[15] = {0};
  scanf("%s", &str);
  // printf("%d\n", a / 100);
  // for (int i = 0; i < strlen(str); i++)
  for (int i = 0; str[i]; i++) //‘\0’
  {
    printf("%c\n", str[i]);
  }
  return 0;
}