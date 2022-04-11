// 实现素数筛
// 1 标记一个范围内的数字是否是合数，没有则标记为素数
// 2 算法空间复杂度为O(n),时间复杂度为O(N*loglogn)
// 3
// 总体思想是用素数去标记掉不是素数的数字，例如我知道了i是素数，那么2*i、3*i...就不是素数

#include <stdio.h>
#define MAX_N 100

int prime[MAX_N + 5] = {0}; //+5 防越界
void init_prime() {
  for (int i = 2; i < MAX_N; i++) {
    if (prime[i]) continue;
    for (int j = 2 * i; j <= MAX_N; j += i) {
      prime[j] = 1;
    }
  }
}
int main() {
  init_prime();
  for (int i = 2; i < 101; i++) {
    if (prime[i]) continue;
    printf("%d\n", i);
  }
  return 0;
}