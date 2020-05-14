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


/* 建立头结点 */
void CreatHead ( PolyList* p );
/* 删除一个节点 */
void DeletePolyNode ( Polynomial node, PolyList* p );
/* 按照次数由低到高连接新元素 */
void AddNewNode ( double coef, int expo, PolyList* p );
/* 删除整个多项式链 */
void DeletePolyList ( PolyList* p );
/* 将 p1 加到 p2 */
void p1_AddTo_p2 ( PolyList* p1, PolyList* p2 );
/* 两多项式相乘 */
PolyList Multi2Polynomial( PolyList* p1, PolyList* p2 );
/* 读取文件中的多项式 */
PolyList ReadPoly ( const char* addr );
/* 输出多项式链 */
void OutputPoly ( const PolyList* p );


int main()
{
    PolyList poly1 = {.head = NULL, .tail = NULL};
    PolyList poly2 = {.head = NULL, .tail = NULL};
    PolyList result = {.head = NULL, .tail = NULL};
    CreatHead( &poly1 );
    CreatHead( &poly2 );
    CreatHead( &result );

    /* 读取多项式 */
    poly1 = ReadPoly("D:\\VS Code\\C\\Algorithmic practice\\poly1.txt");
    poly2 = ReadPoly("D:\\VS Code\\C\\Algorithmic practice\\poly2.txt");

    /* 多项式相加 */
    /* p1_AddTo_p2( &poly1, &poly2 );
    OutputPoly( &poly2 ); */

    OutputPoly(&poly1);
    OutputPoly(&poly2);

    /* 多项式相乘 */
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
            // 更新头结点链长数据
            return;
        }else{  // p 是孤立结点，即链中最后的结点
            p->head = p->tail = NULL;
            free(node);
            node = NULL;
            return;
        }
    }

    if( node->prior && node->next ){    // p 是中间结点
        node->prior->next = node->next;
        node->next->prior = node->prior;
        free(node);
        node = NULL;
        // 更新头结点链长数据
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
{   /* 按照次数由低到高连接新元素 */
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
                // ptr 已经是尾结点了
                break;
            }
        }
        if( ptr->expo == new->expo ){
            // 有相同项，直接加上
            ptr->coef += new->coef;
            if( ptr->coef == 0.0 && ptr->expo != 0 ){ // 避免删除头结点
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
            // 更新尾结点
            p->tail = new;
        }
    }else{  // 这是个空链，只有头结点
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
{   /* p1中每一项乘以 p2，再加到结果链中 */
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
        // 先输出第一项
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