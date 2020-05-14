# include <stdio.h>
# include <stdlib.h>

# define None 0

typedef int ElemType;
typedef struct _node{
    ElemType data;
    struct _node* next;
} Node;
typedef Node* List;

List newList();
void destroyList(List head);
void attachOnHead(List head, ElemType e);
List reverseList(List head);
void outputList(List head);

int main()
{
    List head = newList();

    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        attachOnHead(head, a[i]);
    }
    puts("The origin list:");
    outputList(head);

    reverseList(head);
    puts("The reversed list:");
    outputList(head);

    destroyList(head);

    system("pause");
    return 0;
}

List newList ()
{
    List head = (List)malloc(sizeof(Node));
    head->data = None;
    head->next = NULL;
    return head;
}

void destroyList(List head)
{
    Node* p = head->next;
    while (p) {
        head->next = p->next;
        free(p);
        p = head->next;
    }
    free(head);
}

void attachOnHead(List head, ElemType e)
{
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = e;

    new->next = head->next;
    head->next = new;
}

List reverseList(List head)
{
    static int cnt = 0; // ��¼�ݹ���õĴ�������һ���淴ӳ�˵����Ľ����ţ�cnt == 0ʱ������ǰ������ͷ���
    static List tail;   // ������¼ԭ����β���

    if (head->next) {
        cnt++;
        reverseList(head->next)->next = head;
        cnt--;
        // ���»ص�ͷ��㣬��ͷ������⴦��
        if (cnt == 0) {
            head->next->next = NULL;// ��ʵ head ����һ����ָ��ԭһ�Ž�㣨��β��㣩�����Բٿ���ָ���
            head->next = tail;      // �� head ����һ�����ָ��λ��ԭβ��㣨��һ�Ž�㣩
        }
    } else {
        // ��¼��ԭβ��㣬��һ�Ž��
        tail = head;
    }
    // ���ﷵ�ص��� head ��ʵ����ָ������ֵ�����β���
    return head;
}

void outputList(List head)
{
    Node* p = head->next;

    while (p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    puts("NULL");
}