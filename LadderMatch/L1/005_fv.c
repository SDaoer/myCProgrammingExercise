# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define LEN 17
/* ���ϻ�����Ϊ�����±꣬ʡȥ������������ϻ��� */

typedef struct {
    char stu_NO[LEN];
    int seatNO;
} ShangJiHao;

int main()
{
    int i;
    int N;
    scanf("%d", &N);

    ShangJiHao list[N];
    char temp[LEN];
    int t;

    // ��������
    for( i=0; i < N; i++ ){
        scanf("%s%d", temp, &t);
        temp[LEN-1] = '\0';
        scanf("%d", &list[t].seatNO);
        strcpy( list[t].stu_NO, temp );
        list[t].stu_NO[LEN-1] = '\0';
    }

    // �����������
    int num;
    scanf("%d", &num);
    // ������ҵĺ���
    int search[num];
    for( i=0; i < num; i++ ){
        scanf("%d", &search[i]);
    }
    
    // ����
    for( i=0; i < num; i++ ){
        printf("%s %d\n", list[search[i]].stu_NO, list[search[i]].seatNO);
    }

    system("pause");
    return 0;
}