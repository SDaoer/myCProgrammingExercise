# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_SIZE 10
# define ERROR '\0'

/* 
 * 假设以I和O分别表示入栈和出栈操作，栈的初态和终态均为空，进栈和出栈的操作序列可表示为仅由I和O组成的序列。15
 * （1）下面所示的序列中哪些是合法的？
 *   A.IOIIOIOO  B.IOOIOIIO  C.IIIOIOIO  D.IIIOOIOO
 * （2）通过对（1）的分析，写出一个算法判定所给的操作序列是否合法。若合法返回true；否则返回false（假设被判定的操作序列已存入一维数组中）。
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
        return ERROR;   // ERROR 是 ElemType 的特殊值，标识错误
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
{/* 不合法的情况：执行所有操作后，栈不空 */
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
