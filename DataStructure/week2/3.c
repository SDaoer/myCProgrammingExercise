# include <stdio.h>
# include <stdlib.h>
# define OUT_NUM 3

/* 
**��n����Χ��һȦ��˳���źţ��ӵ�һ���˿�ʼ��������1��3
**��������������3�����˳�Ȧ�ӣ���������µ�����ԭ���ĵڼ�
**�ţ�
*/

int main()
{
/*     int n;
    printf("������������");
    scanf("%d", &n); */
    
    int i = 0, cnt = 1, out = 0;
    
    int m = 0;
    int player[20];
for (int j = 1; j < 15; j++) {
    m = 0;
    out = 0;
    for (i = 0; i < j; i++) {
        player[i] = 0;
    }
    /* ��ʼ������Ϸ */
    for (i = 0, cnt = 1; out < j - 1; i++) {
        m++;
        /* �±�Խ�磬ѭ���±� */
        if (i == j) {
            i = 0;
        }
        /* ��������̭����� */
        if (player[i] == 1) {
            continue;
        }
        /* ��̭��� */
        if (cnt == OUT_NUM) {
            player[i] = 1;
            out++;
            cnt = 1;
            continue;
        }
        cnt++;
    }
    printf("%d-->%d\n", j, m);
}


    /* �ҵ�������� */
    /* �����ϸ�ѭ����������Ϊ out < n; ���� i ����������ҵ���ţ������±�+1��������������� */
    /* for (i = 0; i < n; i++) {
        if ( player[i] == 0 ){
            break;
        }
    } */

    printf("���������%d��\n", i+1);

    system("pause");
    return 0;
}