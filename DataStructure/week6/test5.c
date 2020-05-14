# include <stdio.h>
# include <stdlib.h>

# define None 0

/* �ô�ͷ�ڵ�ĵ������ʾ������ÿ���ڵ���һ���ַ���
 * ���һ���㷨��s���ƽ̨�ĳ��ȣ���νƽ̨��ָ������ͬ�ַ���
 * 
*/

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

int getLongestPlatform(Node* head);

int main()
{
    List string;
    initList(&string);

    char* str = "Ooooohhhhhh!!!Aloha!!";
    int i = 0;

    while (str[i] != '\0'){
        attchOnTail(&string, str[i]);
        i++;
    }

    printf("The longest platform length: %d\n", getLongestPlatform(string.head));

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

int getLongestPlatform(Node* head)
{
    int max_len = 0, len = 0;
    Node* p = head->next;
    Node* q = head; // ����ͷ����ſ��ַ� '\0'    

    while (p) {
        // ��֤ǰ�������ַ��Ƿ����
        if (q->data == p->data) {
            len++;
        } else {
            len = 1;
        }
        // ���� max_len
        if (len > max_len) {
            max_len = len;
        }
        p = p->next;
        q = q->next;
    }

    return max_len;
}