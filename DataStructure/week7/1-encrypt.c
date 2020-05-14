# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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

void encrypt(Node* head, char* encryption);

char* buildDecryption(char* encryption, int len);

int main()
{
    char encryption[] = {
        'n', 'g', 'z', 'q', 't', 
        'c', 'o', 'b', 'm', 'u', 
        'h', 'e', 'l', 'k', 'p', 
        'd', 'a', 'w', 'x', 'f', 
        'y', 'i', 'v', 'r', 's', 'j'
    };

    char* decryption = buildDecryption(encryption, sizeof(encryption)/sizeof(encryption[0]));
    
    for (int i = 0; i < 26; i++){
        printf("%c ", encryption[i]);
    }putchar('\n');
    for (int i = 0; i < 26; i++){
        printf("%c ", decryption[i]);
    }putchar('\n');

    List string;
    initList(&string);
    char* Plaintext = "encrypt";
    for (int i = 0; i < strlen(Plaintext); i++) {
        attchOnTail(&string, Plaintext[i]);
    }

    puts("encrypt:");
    encrypt(string.head, encryption);
    outputList(string.head);

    puts("decrypt:");
    encrypt(string.head, decryption);
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

void encrypt(Node* head, char* encryption)
{
    Node* p = head->next;
    while (p) {
        if ('a' <= p->data && p->data <= 'z') {
            p->data = encryption[p->data - 'a'];
        }
        p = p->next;
    }
}

char* buildDecryption(char* encryption, int len)
{
    char* decryption = (char*)malloc(sizeof(char) * len);

    for (int i = 0; i < len; i++) {
        decryption[encryption[i] - 'a'] = 'a' + i;
    }

    return decryption;
}