# include <stdio.h>
# include <stdlib.h>
# define LIMIT 9

/* ����˷��ھ��� */

int main()
{
    int i, j;

    for (i = 1; i <= LIMIT; i++) {
        for (j = i; j <= LIMIT; j++) {
            printf("%d * %d = %2d\t", i, j, i * j);
        }
        putchar('\n');
    }
    

    system("pause");
    return 0;
}