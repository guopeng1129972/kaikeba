#include <stdio.h>
#include <math.h>
// 将角度值n（90） 转换为弧度值 π（π/2）
#define pi acos(-1)
// 宏的作用 只是符号的替换
int main()
{
  double n;
  while (~scanf("%lf", &n))
  {
    printf("%lf\n", n * pi / 180);
  }
  return 0;
}

// 90
// 1.570796
// 180
// 3.141593

// dobule %lf
// int %d
// scanf("%d",&x)
// %g 取有效数字
// 格式控制字符串 %g
// 格式控制符 g
