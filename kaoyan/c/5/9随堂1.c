// 素数筛
// 1 不为素数 也不是合数
// 2为最小的素数

#include <math.h>
#include <stdio.h>

int is_prime(int n) {
  // 判断大于2之后 去除到n
  // for (int i = 2; i < n; i++) { 法1

  // for (int i = 2; i <= sqrt(n); i++) {  //法2 优化 取小于根n的值
  // 但是存在问题，即 函数sqrt的循环调用问题
  for (int i = 2, I = sqrt(n); i <= I; i++) {  //法3
    // printf("i=%d\n",i);
    if (n % i == 0) return 0;
  }
  return 1;
}
int main() {
  int n;
  while (~scanf("%d", &n)) {
    printf("%d%s\n", n, is_prime(n) ? " is a prime!" : " is not a prime!");
  }
  return 0;
}