# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# define MaxSize 10

typedef int ElemType;

typedef struct {
    ElemType data[MaxSize];
    int top1, top2;
} DStack;

/* ��ʼ��ջ������һ����ջ */
void InitStack(DStack* s);
/* ����ջ���ͷ�ջ s ռ�õĴ洢�ռ� */
void DestoryStack(DStack* s);
/* �ж� i ��ջ�Ƿ�Ϊ������Ϊ�����򷵻��棻���򷵻ؼ� */
bool StackFull(DStack* s);
/* i �Ž�ջ����Ԫ�� e ���뵽ջ s ����Ϊջ��Ԫ�� */
bool Push(DStack* s, int i, ElemType e);
/* i �ų�ջ����ջ s ���˳�ջ��Ԫ�أ�������ֵ���� e */
ElemType Pop(DStack* s, int i);
/* ȡ i ��ջ��Ԫ�ء����ص�ǰ��ջ��Ԫ�أ�������ֵ���� e */
ElemType GetTop(DStack* s, int i);

int main()
{
    DStack s;
    InitStack(&s);

    Push(&s, 1, 12);
    Push(&s, 1, 145);
    Push(&s, 1, 15);
    Push(&s, 2, 123);
    Push(&s, 2, 53);

    puts("1��ջ��");
    printf("Pop: %d\n", Pop(&s, 1));
    printf("Pop: %d\n", Pop(&s, 1));
    printf("Pop: %d\n", Pop(&s, 1));
    puts("2��ջ��");
    printf("Pop: %d\n", Pop(&s, 2));
    printf("Pop: %d\n", Pop(&s, 2));
    Pop(&s, 2);

    system("pause");
    return 0;
}

void InitStack(DStack* s)
{
    s->top1 = -1;
    s->top2 = MaxSize;
}

void DestoryStack(DStack* s)
{
    s->top1 = -1;
    s->top2 = MaxSize;
}

bool StackFull(DStack* s)
{
    return ((s->top1 + 1) >= s->top2);
}

bool Push(DStack* s, int i, ElemType e)
{
    bool success = false;

    if (!StackFull(s)) {
        switch (i) {
        case 1:
            s->top1++;
            s->data[s->top1] = e;
            success = true;
            break;
        case 2:
            s->top2--;
            s->data[s->top2] = e;
            success = true;
            break;
        default:
            puts("ջ�ų���");
            break;
        }
    } else {
        puts("ջ����");
    }

    return success;
}

ElemType Pop(DStack* s, int i)
{
    ElemType result;

    switch (i) {
    case 1:
        if (s->top1 == -1){
            printf("%d��ջ�գ�\n", i);
        } else {
            result = s->data[s->top1];
            s->top1--;
        }
        break;
    case 2:
        if (s->top2 == MaxSize) {
            printf("%d��ջ�գ�\n", i);
        } else {
            result = s->data[s->top2];
            s->top2++;
        }
        break;
    default:
        puts("ջ�ų���");
        break;
    }

    return result;
}

ElemType GetTop(DStack* s, int i)
{
    ElemType result;

    switch (i) {
    case 1:
        if (s->top1 == -1){
            printf("%d��ջ�գ�\n", i);
        } else {
            result = s->data[s->top1];
        }
        break;
    case 2:
        if (s->top2 == MaxSize) {
            printf("%d��ջ�գ�\n", i);
        } else {
            result = s->data[s->top2];
        }
        break;
    default:
        puts("ջ�ų���");
        break;
    }

    return result;
}