# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_SIZE 10
# define ERROR '\0'

/* 假设表达式中允许包含3种括号：圆括号、方括号和大括号。
 * 设计一个算法采用顺序栈判断表达式中的括号是否正确配对。
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
            // 若栈空，返回值是 '\0'，在下面的分支中就会进入 match = false; 符合设计
            // 就不需要再对是否能获得栈顶元素进行判断
            p = getTop(bracket_stack);
            if (p == expression[i] - 1 || 
                p == expression[i] - 2) {
                /* ascii中，'('、')'相差 1，另两对相差 2，且三对括号之间的相差大于 2 */
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