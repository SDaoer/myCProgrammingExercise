# include <stdio.h>
# include <stdlib.h>

# define T 7

int main()
{
    int D;
    scanf("%d", &D);

    int D2;
    D2 = (D+2)%T;
    if( D2 == 0 ){
        D2 = T;
    }

    printf("%d\n", D2);

    system("pause");
    return 0;
}