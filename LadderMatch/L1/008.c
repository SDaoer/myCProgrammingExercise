# include <stdio.h>
# include <stdlib.h>


int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int sum=0, cnt=0;
    for( int i=n; i <= m; i++ ){
        printf("%5d", i);
        sum += i;
        cnt++;
        if( cnt == 5 ){
            putchar('\n');
            cnt = 0;
        }
    }
    // cnt == 0, ˵���ո�����һ�У������ٻ�����
    if( cnt ){
        putchar('\n');
    }
    printf("Sum = %d\n", sum);

    system("pause");
    return 0;
}