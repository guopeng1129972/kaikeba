// 使用指针 实现PE-45函数指针的应用 未实现完
#include <stdio.h>
int tri(int x) { return x * (x + 1) / 2; }
int pen(int y) { return y * (3 * y - 1) / 2; }
int hex(int z) { return z * (2 * z - 1); }
int result(int (*tri)(int), int (*pen)(int), int (*hex)(int), int x, int y,
           int z) {
  return x < 0 ? test1(x) : test2(x);
}
int main() {
  int x;
  while (~scanf("%d", &x)) {
    printf("%d\n", result(test1, test2, x));
  }
  return 0;
}
