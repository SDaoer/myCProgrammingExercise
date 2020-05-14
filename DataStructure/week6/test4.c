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

/* ��ʼ������ */
void initList(List* list);
/* ����������ʣһ����� */
void destoryList(List* list);
/* ���� */
void attchOnTail(List* list, ElemType value);
/* ��� */
int lenOfList(Node* head);
/* ������Ա� */
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
    // �ȶԱ�����п�
    if (list->head->next == NULL) {
        return;
    }
    Node* p = list->head->next;
    Node* q = list->head;
    List digit; // ָ����ʱ������
    initList(&digit);
    List low_alpha; // ָ����ʱСд��ĸ��
    initList(&low_alpha);

    while (p) {
        if ('0' <= p->data && p->data <= '9') {
            // Խ�� p ���
            q->next = p->next;
            // ���� p ���
            p->next = NULL;
            // p ��������� digit ��
            digit.tail->next = p;
            digit.tail = p;
            // �ض�λ p ָ��
            p = q->next;
        } else if ('a' <= p->data && p->data <= 'z') {
            // ��ֹԭ����βָ����·�������ֻ�ᷢ��һ�Σ���β���ȷ�������ٸ���
            if (p == list->tail) {
                list->tail = q;
            }
            // Խ�� p ���
            q->next = p->next;
            // ���� p ���
            p->next = NULL;
            // p ��������� digit ��
            low_alpha.tail->next = p;
            low_alpha.tail = p;
            // �ض�λ p ָ��
            p = q->next;
        } else {
            p = p->next;
            q = q->next;
        }
    }

    // ����ǰ��Σ������ַ���
    digit.tail->next = list->head->next;
    list->head->next = digit.head->next;
    // ���Ӻ��Σ�Сд��ĸ�ַ���
    list->tail->next = low_alpha.head->next;
    // �ͷ�������ʱ������ʱ�����ͷ���
    free(digit.head);
    free(low_alpha.head);

}