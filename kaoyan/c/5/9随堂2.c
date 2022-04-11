// 素数筛
// 1 不为素数 也不是合数
// 2为最小的素数

#include <math.h>
#include <stdio.h>

int is_prime(int n) {
  for (int i = 2, I = sqrt(n); i <= I; i++) {  //法3
    // printf("i=%d\n",i);
    if (n % i == 0) return 0;
  }
  return 1;
}
int main() {
  for (int i = 2; i < 101; i++) {
    // if (is_prime(i)) { 法1 直接写逻辑 问题：存在换行
    //   printf("%d\n", i);
    // }
    if (!is_prime(i)) continue; //法2 当不符合的时候跳过 
    printf("%d\n", i);
  }
  return 0;
}