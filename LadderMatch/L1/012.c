# include <stdio.h>
# include <stdlib.h>

int main()
{
    int a = 1;
    int n;
    scanf("%d", &n);

    printf("2^%d = %d\n", n, a<<n);

    system("pause");
    return 0;
}