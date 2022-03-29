
#include <stdio.h>
int main()
{
  int a, b;
  scanf("%d%d", &a, &b);
  // while (a%b)
  if (a % b == 0)
  {
    printf("YES\n");
  }
  else
  {
    printf("NO\n");
  }
  return 0;
}