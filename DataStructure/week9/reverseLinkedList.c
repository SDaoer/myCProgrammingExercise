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
    static int cnt = 0; // 记录递归调用的次数，另一方面反映了单链的结点序号，cnt == 0时，代表当前是链的头结点
    static List tail;   // 用来记录原链的尾结点

    if (head->next) {
        cnt++;
        reverseList(head->next)->next = head;
        cnt--;
        // 重新回到头结点，对头结点特殊处理
        if (cnt == 0) {
            head->next->next = NULL;// 真实 head 的下一项仍指向原一号结点（现尾结点），可以操控其指向空
            head->next = tail;      // 将 head 的下一个结点指向定位到原尾结点（现一号结点）
        }
    } else {
        // 记录下原尾结点，现一号结点
        tail = head;
    }
    // 这里返回的是 head 但实际上指向的是现单链的尾结点
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