# include <stdio.h>
# include <stdlib.h>

/* 输入一个整数，输出该整数位数，并倒序输出 */

int main()
{
    int n;
    int cnt = 0;
    int mod;

    printf("请输入一个整数：");
    scanf("%d", &n);
    
    printf("倒序为：");
    while (n) {
        mod = n % 10;
        n /= 10;
        cnt++;
        printf("%d", mod);
    }
    if (cnt == 0) { /* 输入整数为 0 的情况 */
        printf("0");
    }
    putchar('\n');

    printf("位数为：%d\n", cnt);

    system("pause");
    return 0;
}