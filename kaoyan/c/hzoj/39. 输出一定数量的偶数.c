#include <stdio.h>

int main()
{
  int begin, b;
  scanf("%d%d", &begin, &b);
  if (begin < 0)
    begin = 0;
  if (begin % 2)
    begin += 1;
  for (int i = 0; i < b; i++)
  {
    printf("%d\n", begin);
    begin += 2;
  }

  return 0;
}