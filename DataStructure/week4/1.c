# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define X 1

typedef struct _node {
    char data;
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
void attchOnTail(List* list, char value);
/* 判断是否表空 */
bool isEmpty(Node* head);
/* 求表长 */
int lenOfList(Node* head);
/* 按序查找 */
Node* find_Kth(Node* head, int k);
/* 按值查找 */
int find_V(Node* head, char value);
/* 插入元素 */
bool insertNode(Node* head, int loc, char value);
/* 删除元素 */
bool deleteNode(Node* head, int loc);
/* 输出线性表 */
void outputList(Node* head);

/* 以 x 为分界，重排链表 */
void departeWith_X(Node* head, int x);

int main()
{
    List list;
    initList(&list);
    int arr[] = {1, 3, 5, -6, -8, 3, -7, -3, 2, -1};

    /* 初始化链表 */
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        attchOnTail(&list, arr[i]);
    }

    /* 输出原链表 */
    puts("原链表为：");
    outputList(list.head);

    /* 以 x 为分界，重排链表 */
    departeWith_X(list.head, X);

    /* 输出重拍后的链表 */
    printf("以%d重排后的链表：\n", X);
    outputList(list.head);

    /* 销毁链表 */
    destoryList(&list);

    system("pause");
    return 0;
}

void initList(List* list)
{
    Node* head_node = (Node*)malloc(sizeof(Node));
    head_node->data = '\0';
    head_node->next = NULL;

    list->head = head_node;
    list->tail = list->head;
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

void attchOnTail(List* list, char value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    list->tail->next = new_node;
    list->tail = new_node;

}

bool isEmpty(Node* head)
{
    return (head->next == NULL);
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

Node* find_Kth(Node* head, int k)
{
    Node* p = head;
    int i = 0;

    while (p->next && i < k) {
        p = p->next;
        i++;
    }

    if (i == k) {
        return p;
    } else {
        return NULL;
    }
}

int find_V(Node* head, char value)
{
    int loc = 0;
    Node* p = head;

    while (p->next && p->data != value) {
        p = p->next;
        loc++;
    }

    if (p->next == NULL) {
        if (p->data != value){
            return 0;
        }
    }

    return loc;
}

bool insertNode(Node* head, int loc, char value)
{
    bool inserted = true;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    Node* p = find_Kth(head, loc - 1);
    if (p) {
        new_node->next = p->next;
        p->next = new_node;
    } else {
        inserted = false;
    }

    return inserted;
}

bool deleteNode(Node* head, int loc)
{
    bool deleted = true;

    Node* p = find_Kth(head, loc - 1);
    if (p) {
        Node* q = p->next;
        p->next = q->next;
        free(q);
    } else {
        deleted = false;
    }
    return deleted;
}

void outputList(Node* head)
{
    Node* p = head->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    putchar('\n');
}

void departeWith_X(Node* head, int x)
{
    Node* q = head;
    Node* p = head->next;
    
    while (p != NULL) {
        
        if (p->data < x) {
            // 越过结点
            q->next = p->next;
            // 连接至头结点之后
            p->next = head->next;
            head->next = p;
            // 重新定位 p 至 q 的后面
            p = q->next;
        } else {
            // 不需移动当前结点，向后检查
            p = p->next;
            q = q->next;
        }

    }

}