# include <stdio.h>
# include <stdlib.h>

int Factorial ( int N );

int main()
{
    int S=0, n;

    scanf("%d", &n);

    for( int i=1; i <= n; i++ ){
        S += Factorial(i);
    }

    printf("%d\n", S);


    system("pause");
    return 0;
}

int Factorial ( int N )
{
    int ret = 1;

    for( int i=2; i <= N; i++ ){
        ret *= i;
    }

    return ret;
}