# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# define MaxSize 10

typedef int ElemType;

typedef struct {
    ElemType data[MaxSize];
    int top1, top2;
} DStack;

/* 初始化栈，构造一个空栈 */
void InitStack(DStack* s);
/* 销毁栈，释放栈 s 占用的存储空间 */
void DestoryStack(DStack* s);
/* 判断 i 号栈是否为满：若为满，则返回真；否则返回假 */
bool StackFull(DStack* s);
/* i 号进栈，将元素 e 插入到栈 s 中作为栈顶元素 */
bool Push(DStack* s, int i, ElemType e);
/* i 号出栈，从栈 s 中退出栈顶元素，并将其值赋给 e */
ElemType Pop(DStack* s, int i);
/* 取 i 号栈顶元素。返回当前的栈顶元素，并将其值赋给 e */
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

    puts("1号栈：");
    printf("Pop: %d\n", Pop(&s, 1));
    printf("Pop: %d\n", Pop(&s, 1));
    printf("Pop: %d\n", Pop(&s, 1));
    puts("2号栈：");
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
            puts("栈号出错！");
            break;
        }
    } else {
        puts("栈满！");
    }

    return success;
}

ElemType Pop(DStack* s, int i)
{
    ElemType result;

    switch (i) {
    case 1:
        if (s->top1 == -1){
            printf("%d号栈空！\n", i);
        } else {
            result = s->data[s->top1];
            s->top1--;
        }
        break;
    case 2:
        if (s->top2 == MaxSize) {
            printf("%d号栈空！\n", i);
        } else {
            result = s->data[s->top2];
            s->top2++;
        }
        break;
    default:
        puts("栈号出错！");
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
            printf("%d号栈空！\n", i);
        } else {
            result = s->data[s->top1];
        }
        break;
    case 2:
        if (s->top2 == MaxSize) {
            printf("%d号栈空！\n", i);
        } else {
            result = s->data[s->top2];
        }
        break;
    default:
        puts("栈号出错！");
        break;
    }

    return result;
}