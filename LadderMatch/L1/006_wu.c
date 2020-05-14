# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/* �ڴ��ڸ��� N�������У�������������������*/
/* ��֤���£�
��������������ӣ�m, m+1������ m>[sqrt(N)]��
��Ӧ�� x, yΪ N�����ӣ����� x*m=N, y*(m+1)=N
��ʽ��˿�֤�� x*yС�� 1���� ��x, yΪ N�����ӡ�ì�ܣ�ԭ������� */

/* �ʶ�ֻ����С�ڵ��� sqrt(N)+1 �ķ�Χ������������
��Ҫע����ǣ����ڵ��� sqrt(N)+1 ��Χ��������������ӣ�
�� sqrt(N)+1 ���ܻ���Ϊ��ǰ���������ӵ����һ�������磺
20��1��2��4��5��10��20
�߽� sqrt(N)+1=5����Ϊǰ���������ӵ����һ���������� */

/* ������֪��������ʣ�µľ��ǲ����������е�����У����Ӷ� o(N) */

int main()
{
    int N;
    int i;
    scanf("%d", &N);

    int limit = (int)sqrt(N) + 1;
    int yinzi[limit];
    int cnt = 0;

    for( i=2; i <= limit; i++ ){
        if( N % i == 0 ){
            yinzi[cnt] = i;
            cnt++;
        }
    }
    yinzi[cnt+1] = 0;
/*     ���㣬��Ϊ���ݱ�������������޷���ʼ���������ٸ�һ��ѭ�����г�ʼ��
    �Լ�������� yinzi[cnt] ǡ�ã����ܿ����Ժ�С����ǰ��Ԫ����������
    ���²������ϵ����Ժ���һλԪ�ظ��㣬��ʶ���� */

    int head, tail;
    int loc_1, loc_2;
    int len=0, max_len=0;
    head = tail = 0;
    loc_1 = loc_2 = 0;
    
    for( i=0; i <= cnt; i++ ){
        // Ѱ����������
        if( yinzi[i+1] == yinzi[i] + 1 ){   // ����
            loc_2 = i+1;
            len = loc_2 - loc_1 + 1;
        }else{  // ���������ض�λ
            loc_1 = i+1;
            len = loc_2 - loc_1;
        }

        // ˢ�����������
        if( len > max_len ){
            head = loc_1;
            tail = loc_2;
            max_len = len;
        }

    }

    if( max_len ){
        printf("%d\n", max_len);
        for( i=head; i < tail; i++ ){
            printf("%d*", yinzi[i]);
        }
        printf("%d\n", yinzi[tail]);
    }else{
        printf("���������ӣ�\n");
    }

    system("pause");
    return 0;
}