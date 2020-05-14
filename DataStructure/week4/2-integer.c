# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define LEN 5
# define ABS(x) ( ((x)>0) ? (x) : (-1*(x)) )

typedef struct _node {
    int data;
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
/* 建表，头插法 */
void attchOnHead(List* list, int value);
/* 建表，尾插法 */
void attchOnTail(List* list, int value);
/* 求表长，不含头结点 */
int lenOfList(Node* head);
/* 输出线性表 */
void outputList(Node* head);

/* 从输入获得长整数 */
void getInteger(List* list);
/* 判断一个字符表示的是否是数字 */
bool isNumber(char c);
/* 将长整数 L2 加到长整数 L1 上 */
void add_p2_to_p1(List* L1, List* L2);
/* 输出结果 */
void outputInteger(List* list);
/* 获得中间结点的值 */
Node* getMiddleNode(Node* head);


int main()
{
    List L2, L1;
    initList(&L2);
    initList(&L1);
    Node* mid;

    for (int i = 0; i < 3; i++){
        getInteger(&L2);
        add_p2_to_p1(&L1, &L2);
        destoryList(&L2);
        initList(&L2);
    }

    mid = getMiddleNode(L1.head);
    printf("The middle number is: %d\n", mid->data);
    outputInteger(&L1);
    destoryList(&L1);

    system("pause");
    return 0;
}

void initList(List* list)
{
    Node* head_node = (Node*)malloc(sizeof(Node));
    head_node->data = 0;
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

void attchOnHead(List* list, int value)
{
    // 初始化一个新结点
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    // 头插法，加到链表中
    new_node->next = list->head->next;
    list->head->next = new_node;
    // 插入第一个结点时，定位尾结点位置
    if (list->head == list->tail) {
        list->tail = new_node;
    }
}

void attchOnTail(List* list, int value)
{
    // 初始化一个新结点
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    // 尾插法，加到链表中
    list->tail->next = new_node;
    list->tail = new_node;
}

int lenOfList(Node* head)
{
    int len = 0;
    Node* p = head->next;

    while (p) {
        len++;
        p = p->next;
    }

    return len;
}

void outputList(Node* head)
{
    Node* p = head->next;
    while (p) {
        printf("%d", p->data);
        p = p->next;
    }
    putchar('\n');
}

void getInteger(List* list)
{
    char x = '\0';
    int sgn = 1;

    printf("Please input an integer:");
    x = getchar();

    if (x == '+' || x == '0'){
        while ((x = getchar()) == '0') {}   // 截取所有前位的 0
    }

    if (x == '-') {
        sgn = -1;
        while ((x = getchar()) == '0') {}   // 截取所有前位的 0
        if (!isNumber(x)) {
            puts("Wrong input!");
        }
    }
    
    // 读取长整数，倒序存在链表中
    while (isNumber(x)) {
        attchOnHead(list, (int)(x-48));
        x = getchar();
    }

    // 更新正负信息
    list->head->data = sgn;
}

bool isNumber(char c)
{
    return ('0' <= c && c <= '9');
}

void add_p2_to_p1(List* L1, List* L2)
{
    int L1_len = lenOfList(L1->head);
    int L2_len = lenOfList(L2->head);

    // 对短的长整数高位补 0
    while (L1_len < L2_len) {
        attchOnTail(L1, 0);
        L1_len++;
    }
    while (L2_len < L1_len) {
        attchOnTail(L2, 0);
        L2_len++;
    }

    Node* p1 = L1->head->next;
    Node* p2 = L2->head->next;
    // 判断是否同号，若任一 0 则被归为同号
    if ((L1->head->data * L2->head->data) > 0) {
        // 同号直接相加
        while (p1 && p2) {
            p1->data += p2->data;
            if (p1->data > 9) {
                p1->data -= 10;
                // 进位
                if (p1->next) {
                    p1->next->data++;
                } else { // 最高位需要进位，则需添加结点
                    attchOnTail(L1, 1);
                    // 更新位数信息
                    L1_len++;
                }
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    } else {
        // 比出两个数绝对值的大小
        Node* a;// 指向大的
        Node* b;// 指向小的
        // 令 q1，q2 指向两个数高位向低位第一个不同的数 / 实际长度不同的情况也在囊括内（因为经过补偿零，形式等长）
        Node* q1 = p1 = L1->head->next;
        Node* q2 = p2 = L2->head->next;
        while (p1 && p2) {
            if (p1->data != p2->data) {
                q1 = p1;
                q2 = p2;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        if (q1->data < q2->data) {
            a = L2->head;
            b = L1->head;
        } else {
            a = L1->head;
            b = L2->head;
        }
        // 结果符号随大数
        L1->head->data = a->data;
        // 大数减小数
        a = a->next;
        b = b->next;
        p1 = L1->head->next;
        while (a && b) {
            a->data -= b->data;
            if (a->data < 0) {
                a->data += 10;
                /* 因为是大数减小数，所以不会有最高位还需要借位的情况
                 * 最多只会借到最高位，最高位不会向后借位了
                 * 因此这里的 a->next->data 是安全的
                 */
                a->next->data --;
            }
            p1->data = a->data;
            a = a->next;
            b = b->next;
            p1 = p1->next;
        }
        // 删除减法可能出现的多余前置 0 
        q1 = p1 = L1->head->next;
        while (p1) {
            // q1 始终指向一个非零结点，最终结果就是指向前置零串的前一位
            if (p1->data != 0) {
                q1 = p1;
            }
            p1 = p1->next;
        }
        // 将 q1 指向第一个前置零，删除全部前置零
        p1 = q1;
        q1 = q1->next;
        while (q1) {
            p1->next = q1->next;
            free(q1);
            q1 = p1->next;
        }
        L1->tail = p1;
    }

}

void outputInteger(List* list)
{
    Node* p = list->head->next;
    List temp;
    initList(&temp);

    while (p) {
        attchOnHead(&temp, p->data);
        p = p->next;
    }

    if (list->head->data < 0) {
        putchar('-');
    }

    outputList(temp.head);
    destoryList(&temp);

}

Node* getMiddleNode(Node* head)
{
    Node* p = head;
    int len = lenOfList(head);
    int mid = len - (len + 1) / 2 + 1;    // 因为长整数是倒序存储的

    for (int i = 0; i < mid; i++){
        p = p->next;
    }

    return p;
}