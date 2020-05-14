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

/* ��ʼ������ */
void initList(List* list);
/* ����������ʣһ����� */
void destoryList(List* list);
/* ����ͷ�巨 */
void attchOnHead(List* list, int value);
/* ����β�巨 */
void attchOnTail(List* list, int value);
/* ���������ͷ��� */
int lenOfList(Node* head);
/* ������Ա� */
void outputList(Node* head);

/* �������ó����� */
void getInteger(List* list);
/* �ж�һ���ַ���ʾ���Ƿ������� */
bool isNumber(char c);
/* �������� L2 �ӵ������� L1 �� */
void add_p2_to_p1(List* L1, List* L2);
/* ������ */
void outputInteger(List* list);
/* ����м����ֵ */
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
    // ��ʼ��һ���½��
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    // ͷ�巨���ӵ�������
    new_node->next = list->head->next;
    list->head->next = new_node;
    // �����һ�����ʱ����λβ���λ��
    if (list->head == list->tail) {
        list->tail = new_node;
    }
}

void attchOnTail(List* list, int value)
{
    // ��ʼ��һ���½��
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    // β�巨���ӵ�������
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
        while ((x = getchar()) == '0') {}   // ��ȡ����ǰλ�� 0
    }

    if (x == '-') {
        sgn = -1;
        while ((x = getchar()) == '0') {}   // ��ȡ����ǰλ�� 0
        if (!isNumber(x)) {
            puts("Wrong input!");
        }
    }
    
    // ��ȡ���������������������
    while (isNumber(x)) {
        attchOnHead(list, (int)(x-48));
        x = getchar();
    }

    // ����������Ϣ
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

    // �Զ̵ĳ�������λ�� 0
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
    // �ж��Ƿ�ͬ�ţ�����һ 0 �򱻹�Ϊͬ��
    if ((L1->head->data * L2->head->data) > 0) {
        // ͬ��ֱ�����
        while (p1 && p2) {
            p1->data += p2->data;
            if (p1->data > 9) {
                p1->data -= 10;
                // ��λ
                if (p1->next) {
                    p1->next->data++;
                } else { // ���λ��Ҫ��λ��������ӽ��
                    attchOnTail(L1, 1);
                    // ����λ����Ϣ
                    L1_len++;
                }
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    } else {
        // �ȳ�����������ֵ�Ĵ�С
        Node* a;// ָ����
        Node* b;// ָ��С��
        // �� q1��q2 ָ����������λ���λ��һ����ͬ���� / ʵ�ʳ��Ȳ�ͬ�����Ҳ�������ڣ���Ϊ���������㣬��ʽ�ȳ���
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
        // ������������
        L1->head->data = a->data;
        // ������С��
        a = a->next;
        b = b->next;
        p1 = L1->head->next;
        while (a && b) {
            a->data -= b->data;
            if (a->data < 0) {
                a->data += 10;
                /* ��Ϊ�Ǵ�����С�������Բ��������λ����Ҫ��λ�����
                 * ���ֻ��赽���λ�����λ��������λ��
                 * �������� a->next->data �ǰ�ȫ��
                 */
                a->next->data --;
            }
            p1->data = a->data;
            a = a->next;
            b = b->next;
            p1 = p1->next;
        }
        // ɾ���������ܳ��ֵĶ���ǰ�� 0 
        q1 = p1 = L1->head->next;
        while (p1) {
            // q1 ʼ��ָ��һ�������㣬���ս������ָ��ǰ���㴮��ǰһλ
            if (p1->data != 0) {
                q1 = p1;
            }
            p1 = p1->next;
        }
        // �� q1 ָ���һ��ǰ���㣬ɾ��ȫ��ǰ����
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
    int mid = len - (len + 1) / 2 + 1;    // ��Ϊ�������ǵ���洢��

    for (int i = 0; i < mid; i++){
        p = p->next;
    }

    return p;
}