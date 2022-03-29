// 计算 成绩对应情况

#include <stdio.h>

int main()
{
  int n;
  scanf("%d", &n);
  if (!n)
  {
    printf("FOOLISH\n");
  }
  else if (n < 60)
  {
    printf("FAIL\n");
  }
  else if (n < 75)
  {
    printf("MEDIUM\n");
  }
  else if (n <= 100)
  {
    printf("GOOD\n");
  }
  else
  {
    printf("GOD\n"); //满分100分 抖一下
  }
  return 0;
}