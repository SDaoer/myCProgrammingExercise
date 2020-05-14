# include <stdio.h>
# include <stdlib.h>



int main()
{
    int cnt = 0;
    long n;
    scanf("%d", &n);

    while( n != 1 ){
        if( n % 2 == 0 ){
            n /= 2;
        }else{
            n = 3*n +1;
        }
        cnt ++;
    }

    printf("%d\n", cnt);

    system("pause");
    return 0;
}