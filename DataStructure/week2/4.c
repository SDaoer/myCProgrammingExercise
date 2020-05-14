# include <stdio.h>
# include <stdlib.h>
# define ID_LEN 18
# define DEPOSITOR_NUM 10

/* 
**��дһ���ṹ�����飬���ڴ洢���е�ʮλ������Ϣ��
**ÿ����������Ϣ�������֤�š��˻���ÿ���˵�
**�ա����ʼ�����鲢������� 
*/

/* ��������
320124198808240056 156.12 9
110108196711301862 6542.21 9
320124198808240056 156.12 9
110108196711301862 6542.21 9
320124198808240056 156.12 9
110108196711301862 6542.21 9
320124198808240056 156.12 9
110108196711301862 6542.21 9
320124198808240056 156.12 9
110108196711301862 6542.21 9

*/

typedef struct {
    char id[ID_LEN + 1];
    float account_balance;
    int monthly_billing_day;
} Depositor;

int checkId(char id[]);

int main()
{
    Depositor depositor[DEPOSITOR_NUM];

    for (int i = 0; i < DEPOSITOR_NUM; i++) {
        printf("�������������֤�ţ�11λ�����˻���ÿ���˵��գ�");
        scanf("%s%f%d", depositor[i].id, &depositor[i].account_balance, &depositor[i].monthly_billing_day);
        if (checkId(depositor[i].id) == 0) {
            printf("���֤�������\n ");
        }
        if (depositor[i].monthly_billing_day > 28 || depositor[i].monthly_billing_day < 1) {
            printf("ÿ���˵�������\n");
        }
    }

    for (int i = 0; i < DEPOSITOR_NUM; i++) {
        printf("���֤��\t\t�˻����\t\tÿ���˵���\n");
        printf("%s\t%.2f\t\t%d\n", depositor[i].id, depositor[i].account_balance, depositor[i].monthly_billing_day);
    }
    
    system("pause");
    return 0;
}

int checkId(char id[]) {
    static const int weight[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    static const char M[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};

    int n, i;
    int check_sum = 0, if_pass = 1;

    for (i = 0; i < ID_LEN-1; i++) {
        if (48 <= id[i] && id[i] <= 57) {
            check_sum += (id[i]-48)*weight[i];
        } else {
            if_pass = 0;
            break;
        }
    }
    if (M[check_sum%11] != id[ID_LEN-1]) {
        if_pass = 0;
    }

    return if_pass;
}