// 生成随机数
#include <stdio.h>
#include <stdlib.h> //rand() random生成随机数字 返回int
#include <time.h>

int main()
{
  srand(time(0));
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int var = rand() % 100;
    // if (i != 0)
    //   printf(", "); 
    i && printf(", ");//格式控制 优化点
    printf("%d", var);
  }
  printf("\n");
  return 0;
}