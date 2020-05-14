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

/* ��ʼ����������ͷ���Ŀ��� */
void initList(PolyList* p);
/* ������������ */
void destroyList(PolyList* p);
/* ɾ����̵�һ����� */
void delSubsequentNode(PolyNode* prior);
/* ����м��뵥��ʽ�������ɵ͵��� */
void addMonomial(double coef, int expo, PolyList* p);
/* ������ʽ��ˣ����ؽ������ʽ */
PolyList multiPolynomial(PolyList* p1, PolyList* p2);
/* �������ʽ���� */
void outputPolynomial(const PolyList* p);
/* ��ȡ�ļ��еĶ���ʽ */
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
    /* �� prior Ϊ�գ���û�к�̽�㣬ʲô��������
     * �� prior->next(del_node) Ϊ�գ����̽��Ϊ�գ�ʲô�������� 
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
    /* ����ʱ��
     * prior ָ�����һ��ָ��С�� expo �Ľ�㣬
     * ptrָ���һ�����ڻ���� expo �Ľ��
     * �� expo == 0���� ptr == prior���� prior->expo == expo == 0
     * ����ͷ��������Ϊ������Ľ��
     * �� ptr �գ���˵�� expo ����������һ��ָ������
     * ���ղ��� prior ֮�󼴿�
     */

    if (ptr && ptr->expo == expo) {
        ptr->coef += coef;
        if (ptr->coef < 1e-6 && ptr != p->head){
            delSubsequentNode(prior);
        }
    } else {
        // ptr->expo > expo���½������� prior ֮��
        PolyNode* monomial = (PolyNode*)malloc(sizeof(PolyNode));
        monomial->coef = coef;
        monomial->expo = expo;
        monomial->next = prior->next;
        prior->next = monomial;
    }
}

PolyList multiPolynomial(PolyList* p1, PolyList* p2)
{
    // �� result ��ֵ����ȥ�����ˣ�result ��ֵ��ָ��������ָ��
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
        // �������һ������
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