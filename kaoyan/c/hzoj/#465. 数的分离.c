#include <math.h>
#include <stdio.h>

int digit(long long n, int k) {
  // 取一个数的位数 log10(n) 下取整 +1 < k 说明没有k位 返回 0
  if (floor(log10(n)) + 1 < k) return 0;
  if (k == 1) return n % 10;
  return digit(n / 10, k - 1);
}

int main() {
  long long n;
  int k;
  scanf("%lld%d", &n, &k);
  printf("%d\n", digit(n, k));
  return 0;
}