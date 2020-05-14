# include <stdio.h>
# include <stdlib.h>

int main()
{
    int n;
    char c;
    int i, j;

    scanf("%d %c", &n, &c);

    for( i=0; i < (int)(n/2.0+0.5); i++ ){
        for( j=0; j < n; j++ ){
            printf("%c", c);
        }
        putchar('\n');
    }

    system("pause");
    return 0;
}