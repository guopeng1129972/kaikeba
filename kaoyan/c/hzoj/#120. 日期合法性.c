
#include <stdio.h>

int check(int y, int m, int d)
{
  if(m<1||m>12) return 0;
  if(d<1||m>31) return 0;
  int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31}; //关键点
  if((y %4==0&& y%100)||y%400==0) month[2]+=1;
  return d<=month[m];

}

int main()
{
  int y, m, d;
  scanf("%d%d%d", &y, &m, &d);
  check(y, m, d);
  printf("%s\n", check(y, m, d) ? "YES" : "NO");
  return 0;
}