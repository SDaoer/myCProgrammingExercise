# include <stdio.h>
# include <stdlib.h>

int main()
{
    int G=0, P=0, L=0, T=0;
    int n=0;
    char c;

    c = getchar();
    while( c != '\n' && n < 10000 ){
        if( c=='G' || c=='g' ){
            G++;
        }
        if( c=='P' || c=='p' ){
            P++;
        }
        if( c=='L' || c=='l' ){
            L++;
        }
        if( c=='T' || c=='t' ){
            T++;
        }
        c = getchar();
    }

    while( G || P || L || T ){
        if( G ){
            putchar('G');
            G--;
        }
        if( P ){
            putchar('P');
            P--;
        }
        if( L ){
            putchar('L');
            L--;
        }
        if( T ){
            putchar('T');
            T--;
        }
    }
    putchar('\n');

    system("pause");
    return 0;
}