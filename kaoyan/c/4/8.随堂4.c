// 实现输入若干个int值，返回最大值
#include <stdarg.h>
#include <stdio.h>
int getMax(int num, ...) {
  int ans = 0;
  va_list arg;
  va_start(arg, num);
  while (num--) {
    int temp = va_arg(arg, int);
    if (temp > ans) ans = temp;
  }
  va_end(arg);
  return ans;
}

int main() {
  printf("%d\n", getMax(4, 2, 3, 4, 5));
  printf("%d\n", getMax(5, 10, 2, 3, 4, 5));

  return 0;
}
