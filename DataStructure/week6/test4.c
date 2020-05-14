# include <stdio.h>
# include <stdlib.h>

# define None 0

typedef char ElemType;
typedef struct _node{
    ElemType data;
    struct _node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

/* 初始化链表 */
void initList(List* list);
/* 销毁链表，不剩一个结点 */
void destoryList(List* list);
/* 建表 */
void attchOnTail(List* list, ElemType value);
/* 求表长 */
int lenOfList(Node* head);
/* 输出线性表 */
void outputList(Node* head);

void divide_Digit_LowAlpha(List* list);

int main()
{
    List string;
    initList(&string);

    char* str = "a1b23D4efg";
    int i = 0;

    while (str[i] != '\0'){
        attchOnTail(&string, str[i]);
        i++;
    }

    divide_Digit_LowAlpha(&string);

    outputList(string.head);

    destoryList(&string);
    system("pause");
    return 0;
}

void initList(List* list)
{
    Node* head_node = (Node*)malloc(sizeof(Node));
    head_node->data = None;
    head_node->next = NULL;
    list->head = list->tail =head_node;
}

void destoryList(List* list)
{
    Node* p = list->head;
    while (list->head) {
        list->head = p->next;
        free(p);
        p = list->head;
    }
    list->tail = list->head = NULL;
}

void attchOnTail(List* list, ElemType value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    list->tail->next = new_node;
    list->tail = new_node;

}

int lenOfList(Node* head)
{
    int len = 0;
    Node* p = head;

    while (p->next) {
        p = p->next;
        len++;
    }

    return len;
}

void outputList(Node* head)
{
    Node* p = head;
    while (p) {
        printf("%c", p->data);
        p = p->next;
    }
    putchar('\n');
}

void divide_Digit_LowAlpha(List* list)
{
    // 先对表进行判空
    if (list->head->next == NULL) {
        return;
    }
    Node* p = list->head->next;
    Node* q = list->head;
    List digit; // 指领临时数字链
    initList(&digit);
    List low_alpha; // 指领临时小写字母链
    initList(&low_alpha);

    while (p) {
        if ('0' <= p->data && p->data <= '9') {
            // 越过 p 结点
            q->next = p->next;
            // 孤立 p 结点
            p->next = NULL;
            // p 结点重连到 digit 链
            digit.tail->next = p;
            digit.tail = p;
            // 重定位 p 指针
            p = q->next;
        } else if ('a' <= p->data && p->data <= 'z') {
            // 防止原链的尾指针迷路，此情况只会发生一次，新尾结点确定不会再改了
            if (p == list->tail) {
                list->tail = q;
            }
            // 越过 p 结点
            q->next = p->next;
            // 孤立 p 结点
            p->next = NULL;
            // p 结点重连到 digit 链
            low_alpha.tail->next = p;
            low_alpha.tail = p;
            // 重定位 p 指针
            p = q->next;
        } else {
            p = p->next;
            q = q->next;
        }
    }

    // 连接前半段（数字字符）
    digit.tail->next = list->head->next;
    list->head->next = digit.head->next;
    // 连接后半段（小写字母字符）
    list->tail->next = low_alpha.head->next;
    // 释放两个临时链建表时申请的头结点
    free(digit.head);
    free(low_alpha.head);

}