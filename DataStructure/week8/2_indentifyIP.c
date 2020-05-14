# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# define NUM 4
# define LEN 3

typedef struct {
    char* str;
    int size;
    int len;
} stirng_block;
typedef stirng_block* String;

String newString_null();
String newString_size(int size);
void destroyString(String s);

typedef String ElemType;
typedef struct _snode{
    ElemType string;
    struct _snode* next;
} SNode;
typedef SNode* SList;

SList newSList();
void destroySList(SList head);
void push(SList head, ElemType elem);
void outputSlist(SList head);

bool checkField(char* field)
{
    bool is_right = true;
    int n = atoi(field);

    if (n > 255 || n < 0) {
        is_right = false;
    }

    return is_right;
}

void checkIP(String IP, SList result)
{
    /* 
     * 遍历字段的位数，根据 begin 获得当前字段
     * 检验当前字段是否合法，合法则检验下一个，
     * （当前检验到第四个（cnt == 4）时，记录到表中）
     * 不合法则返回上一个（return）
     */
    
    static int cnt = 0;         // 当前已验证合法的字段数
    static int begin = 0;       // 记录当前字段的起始索引
    static int dot[NUM] = {0};  // 记录每个点前的字段长度
    char present[LEN + 1] = {'\0'}; // 记录当前字段

    for (int i = 1; i <= LEN; i++) {
        // 获取当前字段
        present[i - 1] = IP->str[begin + i - 1];
        // 检验是否合法
        if (checkField(present)) {
            dot[cnt] = i;
            cnt++;
            if (cnt < NUM) {
                begin += i;
                checkIP(IP, result);
                begin -= i;
            } else if (cnt == NUM && begin + i == IP->len) {
                /* 建立临时字串，将 IP 字串规范化存入临时字串，压入字串链中 */
                int i, j, base = 0;
                String temp = newString_size(IP->size + NUM);
                temp->len = IP->len + NUM - 1;
                for (i = 0; i < NUM; i++) { // NUM - 1: dot 比 field 少 1
                    for (j = 0; j < dot[i]; j++) {
                        temp->str[base + j + i] = IP->str[base + j];
                    }
                    temp->str[base + j + i] = '.';
                    base += dot[i];
                }
                temp->str[temp->len] = '\0';
                push(result, temp);
                destroyString(temp);
            }
            // 对合法字段检验完毕，检验下一种情况是否合法，故 cnt--
            cnt--;
        }
    }

}

int main()
{
    SList result = newSList();

    String IP = newString_size(NUM * LEN + 1);
    printf("input:");
    scanf("%s", IP->str);
    IP->len = strlen(IP->str);

    checkIP(IP, result);
    outputSlist(result);

    destroySList(result);
    destroyString(IP);

    system("pause");
    return 0;
}

String newString_null()
{
    String s = (String)malloc(sizeof(stirng_block));
    s->size = 0;
    s->len = 0;
    s->str = NULL;

    return s;
}

String newString_size(int size)
{
    String s = (String)malloc(sizeof(stirng_block));
    s->size = size;
    s->len = 0;
    s->str = (char*)malloc(sizeof(char) * size);

    return s;
}

void destroyString(String s)
{
    free(s->str);
    s->str = NULL;
    free(s);
}

SList newSList()
{
    SList head = (SList)malloc(sizeof(SNode));
    head->string = newString_null();
    head->next = NULL;
    return head;
}

void destroySList(SList head)
{
    SNode* p = head->next;
    while (p) {
        head->next = p->next;
        destroyString(p->string);
        free(p);
        p = head->next;
    }
    destroyString(head->string);
    free(head);
}

void push(SList head, ElemType elem)
{
    // 复制对象
    ElemType s = newString_size(elem->size);
    s->len = elem->len;
    strcpy(s->str, elem->str);
    // 新建结点
    SNode* p = (SNode*)malloc(sizeof(SNode));
    p->string = s;
    p->next = head->next;
    head->next = p;
}

void outputSlist(SList head)
{
    SNode* p = head->next;
    int i;
    while (p) {
        /* for (i = 0; i < p->string->len; i++) {
            putchar(p->string->str[i]);
        } */
        puts(p->string->str);
        p = p->next;
    }
}