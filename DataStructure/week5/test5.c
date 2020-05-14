# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_SIZE 10
# define ERROR '\0'

/* 
 * ������I��O�ֱ��ʾ��ջ�ͳ�ջ������ջ�ĳ�̬����̬��Ϊ�գ���ջ�ͳ�ջ�Ĳ������пɱ�ʾΪ����I��O��ɵ����С�15
 * ��1��������ʾ����������Щ�ǺϷ��ģ�
 *   A.IOIIOIOO  B.IOOIOIIO  C.IIIOIOIO  D.IIIOOIOO
 * ��2��ͨ���ԣ�1���ķ�����д��һ���㷨�ж������Ĳ��������Ƿ�Ϸ������Ϸ�����true�����򷵻�false�����豻�ж��Ĳ��������Ѵ���һά�����У���
*/

typedef char ElemType;
typedef struct {
    ElemType data[MAX_SIZE];
    int top;
} SNode;
typedef SNode* Stack;

void Push (Stack PtrS, ElemType item)
{
    if (PtrS->top == MAX_SIZE-1){
        printf("The stack is full!\n");
        return;
    } else {
        PtrS->data[++(PtrS->top)] = item;
        return;
    }
}

ElemType Pop (Stack PtrS)
{
    if (PtrS->top == -1){
        printf("The stack is empty!");
        return ERROR;   // ERROR �� ElemType ������ֵ����ʶ����
    } else {
        return (PtrS->data[(PtrS->top)--]);
    }
}

ElemType getTop(Stack s)
{
    if (s->top != -1) {
        return s->data[s->top];
    } else {
        return ERROR;
    }
}

bool operationIllegal(char op[], int n)
{/* ���Ϸ��������ִ�����в�����ջ���� */
    Stack s = (Stack)malloc(sizeof(SNode));
    s->top = -1;
    bool illegal = true;

    for (int i = 0; i < n; i++) {
        if (op[i] == 'I') {
            Push(s, op[i]);
        }
        if (op[i] == 'O') {
            Pop(s);
        }
    }

    if (s->top != -1) {
        illegal = false;
    }

    free(s);

    return illegal;
}

int main()
{
    char op[8];

    gets(op);
    printf("%d\n", operationIllegal(op, 8));
    gets(op);
    printf("%d\n", operationIllegal(op, 8));
    gets(op);
    printf("%d\n", operationIllegal(op, 8));
    gets(op);
    printf("%d\n", operationIllegal(op, 8));


    system("pause");
    return 0;
}
