# include <stdio.h>
# include <stdlib.h>

# define None 0

/* 用带头节点的单链表表示链串，每个节点存放一个字符。
 * 设计一个算法求s中最长平台的长度，所谓平台是指连续相同字符。
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
    Node* q = head; // 链串头结点存放空字符 '\0'    

    while (p) {
        // 验证前后两个字符是否相等
        if (q->data == p->data) {
            len++;
        } else {
            len = 1;
        }
        // 更新 max_len
        if (len > max_len) {
            max_len = len;
        }
        p = p->next;
        q = q->next;
    }

    return max_len;
}