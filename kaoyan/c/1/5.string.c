#include <stdio.h>

int main()
{
  // 字符串数组初始化0
  char str[100] = {0};
  // scanf("%s",str);
  // scanf("%[^\n]s", str);
  while (scanf("%[^\n]s", str) != -1)
  {
    char str1[10];
    str1[0] = getchar();
    printf("%s\n srr1= %c", str, str1[0]);
  }
  // 输入 回车 换行符 空格 制表符 /t ，scanf 会认为是分隔符 终止
  // [] 字符匹配集  ^ 除了
  // [^\n] 除了换行 都可以
  return 0;
}

//gcc

// 输出重定向 a > b
// ./a.out > out
// getchar 读入任何一个字符