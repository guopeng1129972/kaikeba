
#include <stdio.h>
int main() {
  int start, end, sum = 0;
  scanf("%d%d", &start, &end);
  for (; start <= end; start++) {
    if ((start % 4 == 0 && start % 100) || start % 400 == 0) {
      sum += 1;
    }
  }
  printf("%d\n", sum);
  return 0;
}