// 实现素数筛

// 创建数组按顺序存储生成的素数
#include <stdio.h>
#define MAX_N 100

int prime[MAX_N + 5] = {0};  //+5 防越界
// int arr[MAX_N + 5] = {0}, n = 0; //法1
void init_prime() {
  for (int i = 2; i < MAX_N; i++) {
    if (prime[i]) continue;
    // arr[n++] = i; //法1
    prime[++prime[0]] = i;
    for (int j = 2 * i; j <= MAX_N; j += i) {
      prime[j] = 1;
    }
  }
}
int main() {
  init_prime();
  // for (int i = 0; i < n; i++) { //法1
  // printf("%d\n", arr[i]);//法1
  // } //法1
  for (int i = 1; i < prime[0]; i++) {
    printf("%d\n", prime[i]);
  }

  return 0;
}