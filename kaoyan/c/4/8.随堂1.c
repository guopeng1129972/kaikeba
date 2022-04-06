// static 关键字 修饰符 延长变量的声明周期（延长到整个程序被执行完毕）
#include <stdio.h>
void f()
{
  static int a = 0; //使用static修饰的变量会延长到整个程序被执行完毕
  a += 1;
  printf("%d\n", a);
  return;
}

int main()
{
  for (int i = 0; i < 6; i++)
  {
    f();
  }
  return 0;
}

// 1
// 2
// 3
// 4
// 5
// 6