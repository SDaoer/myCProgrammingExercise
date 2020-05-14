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

/* ��ʼ������ */
void initList(List* list);
/* ����������ʣһ����� */
void destoryList(List* list);
/* ���� */
void attchOnTail(List* list, char value);
/* �ж��Ƿ��� */
bool isEmpty(Node* head);
/* ��� */
int lenOfList(Node* head);
/* ������� */
Node* find_Kth(Node* head, int k);
/* ��ֵ���� */
int find_V(Node* head, char value);
/* ����Ԫ�� */
bool insertNode(Node* head, int loc, char value);
/* ɾ��Ԫ�� */
bool deleteNode(Node* head, int loc);
/* ������Ա� */
void outputList(Node* head);

/* �� x Ϊ�ֽ磬�������� */
void departeWith_X(Node* head, int x);

int main()
{
    List list;
    initList(&list);
    int arr[] = {1, 3, 5, -6, -8, 3, -7, -3, 2, -1};

    /* ��ʼ������ */
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        attchOnTail(&list, arr[i]);
    }

    /* ���ԭ���� */
    puts("ԭ����Ϊ��");
    outputList(list.head);

    /* �� x Ϊ�ֽ磬�������� */
    departeWith_X(list.head, X);

    /* ������ĺ������ */
    printf("��%d���ź������\n", X);
    outputList(list.head);

    /* �������� */
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
            // Խ�����
            q->next = p->next;
            // ������ͷ���֮��
            p->next = head->next;
            head->next = p;
            // ���¶�λ p �� q �ĺ���
            p = q->next;
        } else {
            // �����ƶ���ǰ��㣬�����
            p = p->next;
            q = q->next;
        }

    }

}