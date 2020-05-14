# include <stdio.h>
# include <stdlib.h>

int main()
{
    char chr;
    int digits[10] = {0};
    int t;

    while( (chr = getchar()) != '\n' ){
        t = chr - '0';
        digits[t]++;
    }

    for( int i=0; i < 10; i++ ){
        if( digits[i] ){
            printf("%d:%d\n", i, digits[i]);
        }
    }

    system("pause");
    return 0;
}