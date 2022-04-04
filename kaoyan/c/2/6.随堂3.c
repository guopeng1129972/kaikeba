// 实现输出1 2 3 4 5，12345之间空格 5 之后换行
#include <stdio.h>
#include <stdlib.h> //rand() random生成随机数字 返回int
int main()
{
  int num;
  scanf("%d", &num);
  for (int i = 1; i < num+1; i++)
  {
    if (i == num)
    {
      printf("%d\n", i);
    }
    else
    {
      printf("%d ", i);
    }
  }
  return 0;
}