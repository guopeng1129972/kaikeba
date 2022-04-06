
#include <stdio.h>
int main()
{
  int y, m,d;
  scanf("%d%d%d", &y, &m,&d);
  if (y%100==0&& y%400==0){
    if(m==2&&d<29){
      printf("YES\n");
    } else if((m == 4||m==6 || m==9||m==11)&&d<30){
      printf("YES\n");
    } else if(d<31){
       printf("YES\n");
    } else{
      printf("NO\n");
    }
  } else if(y%4==0){
        if(m==2&&d<29){
      printf("YES\n");
    } else if((m == 4||m==6 || m==9||m==11)&&d<30){
      printf("YES\n");
    } else if(d<31){
       printf("YES\n");
    } else{
      printf("NO\n");
    }
  } else if(y%100==0){
    if(m==2&&d<28){
      printf("YES\n");
    } else if((m == 4||m==6 || m==9||m==11)&&d<30){
      printf("YES\n");
    } else if(d<31){
       printf("YES\n");
    } else{
      printf("NO\n");
    }
  }else{
    if(m==2&&d<28){
      printf("YES\n");
    } else if((m == 4||m==6 || m==9||m==11)&&d<30){
      printf("YES\n");
    } else if(d<31){
       printf("YES\n");
    } else{
      printf("NO\n");
    }
  }
  return 0;
}
// 我的 有问题