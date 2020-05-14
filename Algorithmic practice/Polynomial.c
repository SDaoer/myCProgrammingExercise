# include <stdio.h>
# include <stdlib.h>

typedef struct _PolyNode{
    double coef;
    int expo;
    struct _PolyNode* next;
    struct _PolyNode* prior;
} PolyNode;
typedef PolyNode* Polynomial;

typedef struct _poly_list{
    Polynomial head;
    Polynomial tail;
} PolyList;


/* ����ͷ��� */
void CreatHead ( PolyList* p );
/* ɾ��һ���ڵ� */
void DeletePolyNode ( Polynomial node, PolyList* p );
/* ���մ����ɵ͵���������Ԫ�� */
void AddNewNode ( double coef, int expo, PolyList* p );
/* ɾ����������ʽ�� */
void DeletePolyList ( PolyList* p );
/* �� p1 �ӵ� p2 */
void p1_AddTo_p2 ( PolyList* p1, PolyList* p2 );
/* ������ʽ��� */
PolyList Multi2Polynomial( PolyList* p1, PolyList* p2 );
/* ��ȡ�ļ��еĶ���ʽ */
PolyList ReadPoly ( const char* addr );
/* �������ʽ�� */
void OutputPoly ( const PolyList* p );


int main()
{
    PolyList poly1 = {.head = NULL, .tail = NULL};
    PolyList poly2 = {.head = NULL, .tail = NULL};
    PolyList result = {.head = NULL, .tail = NULL};
    CreatHead( &poly1 );
    CreatHead( &poly2 );
    CreatHead( &result );

    /* ��ȡ����ʽ */
    poly1 = ReadPoly("D:\\VS Code\\C\\Algorithmic practice\\poly1.txt");
    poly2 = ReadPoly("D:\\VS Code\\C\\Algorithmic practice\\poly2.txt");

    /* ����ʽ��� */
    /* p1_AddTo_p2( &poly1, &poly2 );
    OutputPoly( &poly2 ); */

    OutputPoly(&poly1);
    OutputPoly(&poly2);

    /* ����ʽ��� */
    result = Multi2Polynomial( &poly1, &poly2 );
    OutputPoly( &result );

    DeletePolyList( &poly1 );
    DeletePolyList( &poly2 );
    DeletePolyList( &result );

    system("pause");
    return 0;
}

void CreatHead ( PolyList* p )
{
    Polynomial new;
    new = (Polynomial)malloc(sizeof(PolyNode));
    new->coef = 0.0;
    new->expo = 0;
    new->next = new->prior = NULL;
    p->head = p->tail = new;
}

void DeletePolyNode ( Polynomial node, PolyList* p )
{
    if( node == p->tail ){
        if( node->prior ){
            p->tail = node->prior;
            node->prior->next = NULL;
            free(node);
            node = NULL;
            // ����ͷ�����������
            return;
        }else{  // p �ǹ�����㣬���������Ľ��
            p->head = p->tail = NULL;
            free(node);
            node = NULL;
            return;
        }
    }

    if( node->prior && node->next ){    // p ���м���
        node->prior->next = node->next;
        node->next->prior = node->prior;
        free(node);
        node = NULL;
        // ����ͷ�����������
        return;
    }
}

void DeletePolyList ( PolyList* p )
{
    Polynomial ptr = p->tail;
    while( ptr ){
        DeletePolyNode( ptr, p );
        ptr = p->tail;
    }
}

void AddNewNode ( double coef, int expo, PolyList* p )
{   /* ���մ����ɵ͵���������Ԫ�� */
    Polynomial new;
    new = (Polynomial)malloc(sizeof(PolyNode));
    new->coef = coef;
    new->expo = expo;
    new->next = new->prior = NULL;

    Polynomial ptr = p->head;
    if( ptr->next ){
        while( ptr->expo < new->expo ){
            if( ptr->next ){
                ptr = ptr->next;
            }else{
                // ptr �Ѿ���β�����
                break;
            }
        }
        if( ptr->expo == new->expo ){
            // ����ͬ�ֱ�Ӽ���
            ptr->coef += new->coef;
            if( ptr->coef == 0.0 && ptr->expo != 0 ){ // ����ɾ��ͷ���
                DeletePolyNode( ptr, p );
            }
            free(new);
        }else if( ptr->expo > new->expo ){
            new->prior = ptr->prior;
            ptr->prior->next = new;
            new->next = ptr;
            ptr->prior = new;
        }else{
            ptr->next = new;
            new->prior = ptr;
            // ����β���
            p->tail = new;
        }
    }else{  // ���Ǹ�������ֻ��ͷ���
        if( new->expo ){
            ptr->next = new;
            new->prior = ptr;
        }else{
            ptr->coef += new->coef;
            free(new);
        }
    }

}

void p1_AddTo_p2 ( PolyList* p1, PolyList* p2 )
{
    Polynomial ptr1;
    ptr1 = p1->head;

    while( ptr1 ){
        AddNewNode( ptr1->coef, ptr1->expo, p2 );
        ptr1 = ptr1->next;
    }

}

PolyList Multi2Polynomial( PolyList* p1, PolyList* p2 )
{   /* p1��ÿһ����� p2���ټӵ�������� */
    PolyList result = {.head = NULL, .tail = NULL};
    CreatHead( &result );

    Polynomial ptr1 = p1->head, ptr2 = p2->head;
    while( ptr1 ){
        while( ptr2 ){
            AddNewNode( ptr1->coef*ptr2->coef, ptr1->expo+ptr2->expo, &result );
            ptr2 = ptr2->next;
        }
        ptr2 = p2->head;
        ptr1 = ptr1->next;
    }

    return result;
}

PolyList ReadPoly ( const char* addr )
{
    int N;
    PolyList poly = {.head = NULL, .tail = NULL};
    CreatHead( &poly );
    FILE* fp = fopen( addr, "r" );
    if( fp ){
        fscanf( fp, "%d\n", &N );
        double coef;
        int expo;
        for( int i=0; i<N; i++ ){
            fscanf( fp, "%lf ", &coef );
            fscanf( fp, "%d\n", &expo );
            AddNewNode( coef, expo, &poly );
        }
    }else{
        printf("Can't open the file.\n");
    }

    return poly;
}

void OutputPoly ( const PolyList* p )
{
    Polynomial ptr = p->head;

    if( ptr ){
        // �������һ��
        if( ptr->coef ){
            printf("%lf", ptr->coef);
        }
        ptr = ptr->next;
    }
    while( ptr ){
        if( ptr->coef < 0 ){
            printf("%lfx^%d", ptr->coef, ptr->expo);
        }else{
            printf("+%lfx^%d", ptr->coef, ptr->expo);
        }
        ptr = ptr->next;
    }
    putchar('\n');
}