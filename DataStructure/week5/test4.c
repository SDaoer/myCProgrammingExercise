# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_SIZE 10
# define ERROR '\0'

/* ������ʽ���������3�����ţ�Բ���š������źʹ����š�
 * ���һ���㷨����˳��ջ�жϱ��ʽ�е������Ƿ���ȷ��ԡ�
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
bool pairBracket(char expression[], int n);

int main()
{
    char* expression = "{[(([])))]}";
    bool match = pairBracket(expression, 10);
    printf("%d\n", match);
    printf("%d\n", false);
    

    system("pause");
    return 0;
}

bool pairBracket(char expression[], int n)
{
    bool match = true;
    Stack bracket_stack = (Stack)malloc(sizeof(SNode));
    bracket_stack->top = -1;
    char p;

    for (int i = 0; i < n; i++) {
        if (expression[i] == '(' || 
            expression[i] == '[' || 
            expression[i] == '{') {
            Push(bracket_stack, expression[i]);
        }
        if (expression[i] == ')' || 
            expression[i] == ']' || 
            expression[i] == '}') {
            // ��ջ�գ�����ֵ�� '\0'��������ķ�֧�оͻ���� match = false; �������
            // �Ͳ���Ҫ�ٶ��Ƿ��ܻ��ջ��Ԫ�ؽ����ж�
            p = getTop(bracket_stack);
            if (p == expression[i] - 1 || 
                p == expression[i] - 2) {
                /* ascii�У�'('��')'��� 1����������� 2������������֮��������� 2 */
                Pop(bracket_stack);
            } else {
                match = false;
            }
        }
    }

    if (bracket_stack->top != -1) {
        match = false;
    }
    free(bracket_stack);
    return match;
}
bool match(char *str)

{

    Stack *s;

    Init(s);

    int i = 0;

    while(str[i] != 0){

        if(IsEmpty(s)){

            push(s,str[i]);

            i++;

            continue;

        }

        if(s->data[s->top] == '(' && str[i] == ')' ||

           s->data[s->top] == '[' && str[i] == ']' ||

           s->data[s->top] == '{' && str[i] == '}'){

            s->top--;

            i++;

            continue;

        }

        push(s,str[i]);

        i++;

    }

    if(IsEmpty(s))

        return true;

    else return false;


}