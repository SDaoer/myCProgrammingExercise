# include <stdio.h>
# include <stdlib.h>

/*
 * ��������˳���L1��L2��˳���ṹ����
 *  typedef struct {
 *      int data[MAX];
 *      int length;
 *  } SqList;
 * ����L1��Ԫ�ص�����L2��Ԫ�صݼ������һ���㷨��
 * ��L1��L2�ϲ�Ϊһ���µ�˳���L3����L3��Ԫ�ص���
 */
# define MAX 10

typedef struct {
    int data[MAX];
    int length;
} SqList;

SqList* ContactTwoSqList(SqList* L1, SqList* L2);

int main()
{
    SqList L1, L2;
    L1.length = 3;
    L2.length = 3;
    printf("L1(length = %d):", L1.length);
    for (int i = 0; i < L1.length; i++) {
        scanf("%d", &L1.data[i]);
    }
    printf("L2(length = %d):", L2.length);
    for (int i = 0; i < L2.length; i++) {
        scanf("%d", &L2.data[i]);
    }

    SqList* L3 = ContactTwoSqList(&L1, &L2);
    for (int i = 0; i < L3->length; i++) {
        printf("%d ", L3->data[i]);
    }
    putchar('\n');


    system("pause");
    return 0;
}

SqList* ContactTwoSqList(SqList* L1, SqList* L2) {
    SqList* L3 = NULL;
    int i, j, k, L1_ok = 1, L2_ok = 1;
    // �ж��Ƿ�L1����L2����
    for (i = 0; i < L1->length - 1; i++){
        if (L1->data[i] > L1->data[i+1]) {
            L1_ok = 0;
        }
    }
    for (i = 0; i < L2->length - 1; i++){
        if (L2->data[i] < L2->data[i+1]) {
            L2_ok = 0;
        }
    }
    if(L1_ok && L2_ok) {
        if (L1->length + L2->length > MAX) { // ���������
            printf("Overflowed!\n");
        } else {
            L3 = (SqList*)malloc(sizeof(SqList));
            for (i = 0, j = 0, k = L2->length - 1; j < L1->length && k >= 0; i++) {
                if (L1->data[j] < L2->data[k]) {
                    L3->data[i] = L1->data[j];
                    j++;
                } else {
                    L3->data[i] = L2->data[k];
                    k--;
                }
            }
            while (j < L1->length) {
                L3->data[i] = L1->data[j];
                i++;
                j++;
            }
            while (k >= 0) {
                L3->data[i] = L2->data[k];
                i++;
                k--;
            }
            L3->length = L1->length + L2->length;
        }

    }


    return L3;
}