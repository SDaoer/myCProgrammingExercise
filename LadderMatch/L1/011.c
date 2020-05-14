# include <stdio.h>
# include <stdlib.h>

int main()
{
    char a[10001], b[10001];
    int chart[128] = {0};   // 封禁表，标 1 表示被封禁
    int i=0;

    gets(a);
    gets(b);
    
    while( b[i] ){
        chart[b[i]] = 1;
        i++;
    }

    i=0;
    while( a[i] ){
        if( chart[a[i]] == 0 ){
            printf("%c", a[i]);
        }
        i++;
    }
    putchar('\n');

    system("pause");
    return 0;
}