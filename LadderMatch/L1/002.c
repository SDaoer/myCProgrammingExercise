# include <stdio.h>
# include <math.h>
# include <stdlib.h>

int main()
{
    int N;
    char chr;
    scanf("%d %c", &N, &chr);

    // ¼ÆËãÐÐÊý
    int m;
    m = (int)sqrt( (N+1)/2 );

    int i, j, k;
    for( i=m; i > 0; i-- ){
        for( k=m-i; k > 0; k-- ){
            putchar(' ');
        }
        for( j=0; j < 2*i-1; j++ ){
            putchar(chr);
        }
        putchar('\n');
    }
    for( i=2; i <= m; i++ ){
        for( k=m-i; k > 0; k-- ){
            putchar(' ');
        }
        for( j=0; j < 2*i-1; j++ ){
            putchar(chr);
        }
        putchar('\n');
    }

    printf("%d\n", N-(2*m*m-1));

    system("pause");
    return 0;
}