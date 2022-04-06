// 使用指针
#include <stdio.h>
int test1(int x) { return x * x; }
int test2(int x) { return x + 2; }
int result(int (*test1)(int), int (*test2)(int), int x) {
  return x < 0 ? test1(x) : test2(x);
}
int main() {
  int x;
  while (~scanf("%d", &x)) {
    printf("%d\n", result(test1, test2, x));
  }
  return 0;
}
