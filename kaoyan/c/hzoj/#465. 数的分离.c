
#include <stdio.h>
#include <string.h>

int main() {
  char n[15] = {0};
  int k;
  scanf("%s%d", &n, &k);
  printf("%c\n", n[strlen(n) - k]);
  return 0;
}