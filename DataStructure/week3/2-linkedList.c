# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define LEN 5

typedef char ElemType;
typedef struct _node {
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
/* 判断是否表空 */
bool isEmpty(Node* head);
/* 求表长 */
int lenOfList(Node* head);
/* 按序查找 */
Node* find_Kth(Node* head, int k);
/* 按值查找 */
int find_V(Node* head, ElemType value);
/* 插入元素 */
bool insertNode(Node* head, int loc, ElemType value);
/* 删除元素 */
bool deleteNode(Node* head, int loc);
/* 输出线性表 */
void outputList(Node* head);

int main()
{
    List list;
    initList(&list);
    ElemType arr[LEN] = {'a', 'b', 'c', 'd', 'e'};

    for (int i = 0; i < LEN; i++) {
        attchOnTail(&list, arr[i]);
    }
    outputList(list.head);
    printf("链表长度：%d\n", lenOfList(list.head));
    printf("链表空否：%d\n", isEmpty(list.head));
    printf("链表第三个元素：%c\n", (find_Kth(list.head, 3))->data);
    printf("元素a在链表中的位置：%d\n", find_V(list.head, '\a'));
    
    insertNode(list.head, 4, 'f');
    printf("在第四个元素位置插入'f'：");
    outputList(list.head);

    deleteNode(list.head, 3);
    printf("删除链表第3个元素：");
    outputList(list.head);

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

void attchOnTail(List* list, ElemType value)
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

int find_V(Node* head, ElemType value)
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

bool insertNode(Node* head, int loc, ElemType value)
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
    Node* p = head;
    while (p) {
        printf("%c", p->data);
        p = p->next;
    }
    putElemType('\n');
}
