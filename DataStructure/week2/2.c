# include <stdio.h>
# include <stdlib.h>

/* ����һ�����������������λ������������� */

int main()
{
    int n;
    int cnt = 0;
    int mod;

    printf("������һ��������");
    scanf("%d", &n);
    
    printf("����Ϊ��");
    while (n) {
        mod = n % 10;
        n /= 10;
        cnt++;
        printf("%d", mod);
    }
    if (cnt == 0) { /* ��������Ϊ 0 ����� */
        printf("0");
    }
    putchar('\n');

    printf("λ��Ϊ��%d\n", cnt);

    system("pause");
    return 0;
}