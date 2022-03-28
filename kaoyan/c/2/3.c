#include <stdio.h>
#include <math.h>
// 计算一个数x的立方根
int main()
{
  int a, b;
  scanf("%d%d", &a, &b);
  printf("a=%d,b=%d\n", a, b);
  // 1.交换
  // int temp = a;
  // a = b;
  // b = temp;
  // printf("swap a,b a=%d,b=%d\n", a, b);
  // 2.异或 位运算仅支持int
  a ^= b; //a1= a ^ b
  b ^= a; //b=b^a1
  a ^= b;
  printf("swap a,b a=%d,b=%d\n", a, b);
  return 0;
}

// （1） 0 ^ 0 = 0，0 ^ 1 = 1 0异或任何数＝任何数

// 　　（2） 1 ^ 0 = 1，1 ^ 1 = 0 1异或任何数－任何数取反

// 　　（3） 任何数异或自己＝把自己置0