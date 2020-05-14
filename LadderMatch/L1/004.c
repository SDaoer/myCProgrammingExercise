# include <stdio.h>
# include <stdlib.h>

int main()
{
    int F, C;
    scanf("%d", &F);

    C = 5*(F-32)/9;
    printf("Celsius = %d\n", C);

    system("pause");
    return 0;
}