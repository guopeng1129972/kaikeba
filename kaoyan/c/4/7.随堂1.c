// 生成随机数
// 实现 6.随堂4.c的 输出当前存在奇数项
#include <stdio.h>
#include <stdlib.h> //rand() random生成随机数字 返回int
#include <time.h>

int main()
{
  srand(time(0));
  int n;
  int sum = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int var = rand() % 100;
    
    // if (var % 2 == 1) // 方案一 
    // if (var & 1) // 方案2 优化取模2来判断是否为奇数
    // {
    //   sum++;
    // }
    sum+=(var & 1); //方案2 优化2
    i &&printf(", "); //格式控制 优化点
    printf("%d", var);
  }
  printf("\n");
  printf("%d\n", sum);
  return 0;
}