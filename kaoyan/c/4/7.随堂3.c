// 实现一个程序，读入n，计算n的阶乘
#include <stdio.h>
#define NUM_MAX 2000000     //测试爆栈
// int arr[NUM_MAX + 5] = {0}; //当n为全局变量，大于11时就不会爆栈

int f(int n)
{
  // int arr[NUM_MAX+5]={0};// 当n大于11时就会爆栈
  if (n == 1)
  {
    return n;
  }
  return n * f(n - 1);
}

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    printf("%d\n", f(n));
  }
  // 方案1 不能循环输出的
  // scanf("%d", &n);
  // printf("%d\n", f(n));
  return 0;
}