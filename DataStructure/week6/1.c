# include <stdio.h>
# include <stdlib.h>

typedef struct _PolyNode{
    double coef;
    int expo;
    struct _PolyNode* next;
} PolyNode;
typedef PolyNode* Polynomial;

typedef struct _poly_list{
    Polynomial head;
} PolyList;

/* 初始化，建立带头结点的空链 */
void initList(PolyList* p);
/* 销毁整个链表 */
void destroyList(PolyList* p);
/* 删除后继的一个结点 */
void delSubsequentNode(PolyNode* prior);
/* 向表中加入单项式，次数由低到高 */
void addMonomial(double coef, int expo, PolyList* p);
/* 两多项式相乘，返回结果多项式 */
PolyList multiPolynomial(PolyList* p1, PolyList* p2);
/* 输出多项式链表 */
void outputPolynomial(const PolyList* p);
/* 读取文件中的多项式 */
void readPolynomial(const char* addr, PolyList* p);

int main()
{
    PolyList poly1, poly2;
    initList(&poly1);
    initList(&poly2);

    readPolynomial("DataStructure\\week6\\poly2.txt", &poly2);
    readPolynomial("DataStructure\\week6\\poly1.txt", &poly1);

    outputPolynomial(&poly1);
    outputPolynomial(&poly2);

    PolyList result = multiPolynomial( &poly1, &poly2 );
    outputPolynomial( &result );

    destroyList(&poly1);
    destroyList(&poly2);
    destroyList(&result);

    system("pause");
    return 0;
}

void initList(PolyList* p)
{
    PolyNode* head = (PolyNode*)malloc(sizeof(PolyNode));
    head->coef = 0.0;
    head->expo = 0;
    head->next = NULL;
    p->head = head;
}

void destroyList(PolyList* p)
{
    PolyNode* ptr1 = p->head;
    PolyNode* ptr2 = p->head->next;

    while (ptr2) {
        ptr1->next = ptr2->next;
        free(ptr2);
        ptr2 = ptr1->next;
    }
    free(ptr1);
    p->head = NULL;
}

void delSubsequentNode(PolyNode* prior)
{
    if (prior && prior->next) {
        PolyNode* del_node = prior->next;
        prior->next = del_node->next;
        free(del_node);
    }
    /* 若 prior 为空，则没有后继结点，什么都不用做
     * 若 prior->next(del_node) 为空，则后继结点为空，什么都不用做 
     */
}

void addMonomial(double coef, int expo, PolyList* p)
{
    PolyNode* ptr = p->head;
    PolyNode* prior = ptr;

    while (ptr && ptr->expo < expo) {
        prior = ptr;
        ptr = ptr->next;
    }
    /* 结束时：
     * prior 指向最后一个指数小于 expo 的结点，
     * ptr指向第一个大于或等于 expo 的结点
     * 若 expo == 0，则 ptr == prior，且 prior->expo == expo == 0
     * 所以头结点可以作为常数项的结点
     * 若 ptr 空，则说明 expo 比链中任意一项指数都大
     * 按照插在 prior 之后即可
     */

    if (ptr && ptr->expo == expo) {
        ptr->coef += coef;
        if (ptr->coef < 1e-6 && ptr != p->head){
            delSubsequentNode(prior);
        }
    } else {
        // ptr->expo > expo，新建结点插入 prior 之后
        PolyNode* monomial = (PolyNode*)malloc(sizeof(PolyNode));
        monomial->coef = coef;
        monomial->expo = expo;
        monomial->next = prior->next;
        prior->next = monomial;
    }
}

PolyList multiPolynomial(PolyList* p1, PolyList* p2)
{
    // 把 result 的值传出去就行了，result 的值是指向结果链的指针
    PolyList result;
    initList(&result);

    PolyNode* ptr1 = p1->head;
    PolyNode* ptr2 = p2->head;

    while (ptr1) {
        while (ptr2) {
            addMonomial(ptr1->coef * ptr2->coef, ptr1->expo + ptr2->expo, &result);
            ptr2 = ptr2->next;
        }
        ptr2 = p2->head;
        ptr1 = ptr1->next;
    }

    return result;
}

void outputPolynomial(const PolyList* p)
{
    PolyNode* ptr = p->head;
    if (ptr) {
        // 先输出第一项（常数项）
        if (ptr->coef) {
            printf("%lf", ptr->coef);
        }
        ptr = ptr->next;
    }
    while (ptr) {
        if (ptr->coef < 0) {
            printf("%lfx^%d", ptr->coef, ptr->expo);
        } else {
            printf("+%lfx^%d", ptr->coef, ptr->expo);
        }
        ptr = ptr->next;
    }
    putchar('\n');
}

void readPolynomial(const char* addr, PolyList* p)
{
    FILE* fp = fopen(addr, "r");
    if (fp) {
        int n;
        fscanf(fp, "%d\n", &n);
        double coef;
        int expo;
        for (int i=0; i<n; i++) {
            fscanf(fp, "%lf ", &coef);
            fscanf(fp, "%d\n", &expo);
            addMonomial(coef, expo, p);
        }
    } else {
        printf("Can't open the file.\n");
    }
}