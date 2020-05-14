# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define ABS(x) ( ((x)>0) ? (x) : (-1*(x)) )

clock_t start, stop;
double duration;

/* READ ME��
1�� ��������ʱ�Ӻ���ǰ���㣬��������ĩλ����Ҫ���ĩλ
    ��������ʱ����Ҫ�ȴ����λ
    ����� TailAttch �޷�ͳһ
    ���Ƕ�������ʹ�ö�ջ�ṹ���Խ����ʹ�ö��нṹ���������޷�ͳһ���ݽṹ
    ֻ�ù������� TailAttch��һ����ǰ���һ���Ӻ���ǰ
*/

typedef struct _NumberNode* Number;
typedef struct _NumberNode{
    int num;
    Number next;
    Number prior;
} NumberNode;

// Integer ���ʹ����������ͷβָ��
typedef struct {
    Number head;
    Number tail;
} Integer;



/* ����һ��ͷ��� */
Integer CreateHead ( int sign );
/* ��ͷ�����������Ԫ�� */
void TailAttch ( int number, Integer* integer );
/* ��β�����������Ԫ�� */
void HeadAttch ( int number, Integer* integer );
/* ����һ������ */
Integer InputInteger ( void ); //  ���� CreateHead �� TailAttch ����
/* ���һ������ */
void OutputInteger ( Number p );
/* ����������� */
Integer Add2Integer ( Integer* integer1, Integer* integer2 );
/* ͬ�ź� */
Integer PPorNN_Add ( Integer* integer1, Integer* integer2 );
/* ��ź� */
Integer PN_Add ( Integer* integer1, Integer* integer2 );
/* �Ƚϴ�С */
int Compare2Integer_Abs ( Number head1, Number head2 );

/* ɾ��һ�����ֽ�� */
void DeleteNode ( Number p, Integer* integer );
/* ɾ������������ */
void DeleteInteger ( Integer* integer );

/* ���ļ�����һ������ */
Integer ReadInteger ( FILE* const fp );

/* ����������� */
Integer Multiply2Integer ( Integer* integer1, Integer* integer2 );
/* ��λ�淶�� */
void CarryCanonicalize ( Integer* integer );//������Ҫ�ı���ͷ����Ҫ��ָ��
/* ȥ�㺯��������ȥ�������� */
int Throw0 ( Integer *integer);

Integer DaShuJieCheng( int n );// ��� n��Ӧ���� 2**32-2**32/10 �� 2**32/9 ֮���ĳ��������ʮ�ڵ�����

int main ()
{
    // Q1
/*     Integer integer1;
    integer1.head = integer1.tail = NULL;
    Integer integer2;
    integer2.head = integer2.tail = NULL;
    Integer ret;
    ret.head = ret.tail = NULL;

    while(1){
        integer1 = InputInteger();
        OutputInteger(integer1.head);
        integer2 = InputInteger();
        OutputInteger(integer2.head);

        ret = Add2Integer( &integer1, &integer2 );
        OutputInteger(ret.head);
        DeleteInteger( &integer1 );
        DeleteInteger( &integer2 );
        DeleteInteger( &ret );
    } */

    // Q2
    /* start = clock();

    int num_of_lines;
    char chr;
    FILE* fp = fopen( "D:\\VS Code\\C\\Algorithmic practice\\input1.txt", "r" );
    if( fp ){
        fscanf( fp, "%d\n", &num_of_lines );
        Integer temp;
        temp.head = temp.tail = NULL;
        Integer sum;
        sum.head = sum.tail = NULL;
        sum = CreateHead(0);

        for( int i = 0; i < num_of_lines; i++ ){
            temp = ReadInteger( fp );
            sum = Add2Integer( &sum, &temp );
            DeleteInteger( &temp );
        }

        OutputInteger( sum.head );
        DeleteInteger( &sum );

    }else{
        printf("Can't open the file.\n");
    }

    stop = clock();
    duration = ((double)(stop-start))/CLK_TCK;
    printf("\n\nTime cost:%lfs\n\n", duration); */

    // Q3
    // test
/*     Integer integer1;
    integer1.head = integer1.tail = NULL;
    Integer integer2;
    integer2.head = integer2.tail = NULL;
    Integer ret;
    ret.head = ret.tail = NULL;

    while(1){
        integer1 = InputInteger();
        OutputInteger(integer1.head);
        integer2 = InputInteger();
        OutputInteger(integer2.head);

        ret = Multiply2Integer( &integer1, &integer2 );
        OutputInteger(ret.head);
        DeleteInteger( &integer1 );
        DeleteInteger( &integer2 );
        DeleteInteger( &ret );
    } */

/*     Integer temp;
    temp.head = temp.tail = NULL;
    Integer sum;
    sum.head = sum.tail = NULL;
    sum = CreateHead(0);
    for( int i=1; i <= 100; i++ ){
        temp = DaShuJieCheng(i);
        sum = Add2Integer( &sum, &temp );
    }
    OutputInteger( sum.head );
    DeleteInteger( &sum ); */

    system("pause");
    return 0;
}


Integer CreateHead ( int sign )
{
    /*
    1������ͷ��㣬ʵ��������������ʾ��1������ -1���� 0�������
    2��ͷ��㻹������������������ӽ�㣬��ͷ��� num++�����������ӽ�㣬��ͷ��� num--
    */
    Integer new_integer;
    new_integer.head = new_integer.tail = (Number)malloc(sizeof(NumberNode));
    new_integer.head->num = sign;
    new_integer.head->next = new_integer.head->prior = NULL;

    return new_integer;
}

void TailAttch ( int number, Integer* integer )
{
    // �����½��
    Number new_num;
    new_num = (Number)malloc(sizeof(NumberNode));
    new_num->num = number;
    // �����½��
    new_num->prior = integer->tail;
    new_num->next = NULL;
    new_num->prior->next = new_num;
    // �ض�λβָ��
    integer->tail = new_num;

    // ��������
    if( integer->head->num > 0 ){
        integer->head->num++;
    }else if( integer->head->num < 0 ){
        integer->head->num--;
    }
}
void HeadAttch ( int number, Integer* integer )
{
    // �����½��
    Number new_num;
    new_num = (Number)malloc(sizeof(NumberNode));
    new_num->num = number;
    new_num->next = NULL;
    // �����½��
    if(integer->head->next){
    // ͷ���֮���н��
        // �����½��
        new_num->prior = integer->head;
        new_num->next = integer->head->next;
        integer->head->next = new_num;
        new_num->next->prior = new_num;
    }else{
    // ��ͷ���
        // �����½��
        new_num->prior = integer->head;
        new_num->next = integer->head->next;
        integer->head->next = new_num;
        // �ض�λβָ��
        integer->tail = new_num;
    }

    // ��������
    if( integer->head->num > 0 ){
        integer->head->num++;
    }else if( integer->head->num < 0 ){
        integer->head->num--;
    }
}

Integer InputInteger ( void )
{
    Integer integer;
    integer.head = integer.tail = NULL;
    int t;

    char sgn;
    printf("Please input an integer:");
    // �ȶ���һ��
    scanf("%c", &sgn);
    
    // �ж���������������ͷ��� �Լ� ��һ������
    if( sgn == '+' || sgn == '0' ){
        while( (sgn = getchar()) == '0' ){}   // ��ȡ����ǰλ�� 0
        // ��õ�һ����������
        t = (int)(sgn-48);
        integer = CreateHead(1);
        TailAttch( t, &integer );
    }else if( sgn == '-' ){
        while( (sgn = getchar()) == '0' ){}   // ��ȡ����ǰλ�� 0
        // ��õ�һ����������
        t = (int)(sgn-48);
        integer = CreateHead(-1);
        TailAttch( t, &integer );
    }else if( sgn >= 49 && sgn <= 57 ){ // sgn ���յ���������
        t = (int)(sgn-48);
        integer = CreateHead(1);
        TailAttch( t, &integer );
    }else{
        puts("Wrong input!");
        return integer;
    }

    while( (sgn = getchar()) != '\n' ){
        t = (int)(sgn-48);
        TailAttch( t, &integer );
    }

    return integer; // ���أ����������ͷβ��Ϣ integer

}

void OutputInteger ( Number p )
{
    // �����������Ϣ
    if( p->num < 0 ){
        // ͷ�������С�� 0������
        putchar('-');
    }else if( p->num == 0 ){
        // ͷ�������Ϊ 0����Ϊ 0
        puts("0");
        return;
    }
    p = p->next;


    while( p ){
        printf("%d", p->num);
        p = p->next;
    }

    putchar('\n');

}

Integer Add2Integer ( Integer* integer1, Integer* integer2 )
{
    /*
    1�����ж���������������������ʹ����������
        # ͬ����̳з��ţ�Ȼ�����
        # ������ȱȾ��Դ�С
            $ �ȱ�����
            $ ������һλһλ�Ƚ�
          ��֤�Ǵ�ļ�С�ģ�Ȼ���������
    2������ʱ����ֱ�ӴӺ���ǰ����ÿ�����
       ��ŵ���������ٽ��� ���淶����
        # ��ӵĹ淶����Ҫ���н�λ����
        # ����Ĺ淶����Ҫ���н�λ����
        # ����淶������Ҫ����ӳ�����ǰλ 0 ��ɾ��
    */
    Integer ret;
    ret.head = ret.tail = NULL;

    if( (integer1->head->num ^ integer2->head->num) >= 0 ){
    // ���� ͬ����ӡ�����+0��0+0
        ret = PPorNN_Add( integer1, integer2 );
    }else{
    // ���� �����ӡ�����+0
        switch ( Compare2Integer_Abs( integer1->head, integer2->head ) ){
        case 1:
            ret = PN_Add( integer1, integer2 );
            break;
        case -1:
            ret = PN_Add( integer2, integer1 );
            break;
        default:    // ������ȫ���
            ret = CreateHead(0); 
            break;
        }

    }

    return ret;
}


Integer PPorNN_Add ( Integer* integer1, Integer* integer2 )
{
    Integer ret;
    ret.head = ret.tail = NULL;
    Number p1, p2;
    p1 = integer1->tail;
    p2 = integer2->tail;

    // ���������� ������Ϣ
    if( integer1->head->num > 0 ){
        ret = CreateHead(1);
    }else if( integer1->head->num < 0 ){
        ret = CreateHead(-1);
    }else{  // integer1 �ǿ������ٶ� integer2 �ж�
        if( integer2->head->num == 0 ){
            // �������� 0���������㣬ֱ�ӷ���
            return *integer1;
        }else{
            // integer2 �� 0��ֱ�ӷ��� integer2 ��Ϊ���
            return *integer2;
        }
    }

    // ֱ�ӴӺ���ǰ���
    while( (p1 != integer1->head) && (p2 != integer2->head) ){
        HeadAttch( p1->num + p2->num, &ret );
        p1 = p1->prior;
        p2 = p2->prior;
    }
    // ��һ��ָ�� ����ͷ����
    while( p1 != integer1->head ){
        HeadAttch( p1->num, &ret );
        p1 = p1->prior;

    }
    while( p2 != integer2->head ){
        HeadAttch( p2->num, &ret );
        p2 = p2->prior;
    }

    /* ��λ�淶�� */
    // �ӷ�ʱ��λ���ֻ���λ 1λ������Ҫ���ǳ˷�����
    Number p3 = ret.tail;
    while( p3 != ret.head->next ){
        if( p3->num > 9 ){
            p3->num %= 10;
            p3->prior->num ++;
        }
        p3 = p3->prior;
    }
    // p3 ����ͷ���ǰһλ���������ĵ�һλ
    if( p3->num > 9 ){
        p3->num %= 10;
        // ��ͷ��������һ�����ֽ��
        HeadAttch( 1, &ret );
    }

    return ret;
}

Integer PN_Add ( Integer* integer1, Integer* integer2 )
{
    // �����ʱ�򣬹��ھ���ֵ��ǰ�ߴ��ں���

    Integer ret;
    ret.head = ret.tail = NULL;
    Number p1, p2;
    p1 = integer1->tail;
    p2 = integer2->tail;

    // ���������� ������Ϣ
    ret = CreateHead(integer1->head->num/ABS(integer1->head->num));
    // ֱ�ӴӺ���ǰ���
    while( p2 != integer2->head ){
        HeadAttch( p1->num - p2->num, &ret );
        p1 = p1->prior;
        p2 = p2->prior;
    }
    // p2 ����ͷ����
    while( p1 != integer1->head ){
        HeadAttch( p1->num, &ret );
        p1 = p1->prior;
    }

    /* ��λ�淶�� */
    Number p3 = ret.tail;
    while( p3 != ret.head->next ){
        if( p3->num < 0 ){
            p3->num += 10;
            p3->prior->num --;
        }
        p3 = p3->prior;
    }
    // �����Ǵ�����С��������ֻ��Ҫ��������ͷһλ�Ƿ��� 0����λ�������������ȥ����
    // p3 ����ͷ���ǰһλ���������ĵ�һλ
    if( p3->num == 0 ){
        DeleteNode( p3, &ret );
    }

    return ret;
}

int Compare2Integer_Abs ( Number head1, Number head2 )
{
    // ���ڷ��� 1��С�ڷ��� -1����ȷ��� 0

    int ret;

    if( ABS(head1->num) > ABS(head2->num) ){
        ret = 1;
    }else if( ABS(head1->num) < ABS(head2->num) ){
        ret = -1;
    }else{  // ����ȳ����ȸ�λ���ִ�С
        head1 = head1->next;
        head2 = head2->next;
        while( head1 ){    // �����ߵȳ�����������һ������
            if( head1->num > head2->num ){
                ret = 1;
                break;  // �ȳ���С�ˣ��˳�ѭ��
            }else if( head1->num < head2->num ){
                ret = -1;
                break;  // �ȳ���С�ˣ��˳�ѭ��
            }else{
                // û�ȳ���С����λ����
                head1 = head1->next;
                head2 = head2->next;
                ret = 0;
            }
        }
    }

    return ret;

}

void DeleteNode ( Number p, Integer* integer )
{
    /*  ɾ���м���������һ����٣�ֻ�����������λ
        ���õ��������ܵ��ǵ�Ҫɾ��������������ʱ��
        ɾ��������������ʱ�򣬴�β�Ϳ�ʼ��ɾ��ͷ���(����β���ɾ��)�����漰�м���
        �ʰ�β����жϷ�����ǰ�棬��β����м��� */

    if( p == integer->tail ){    // p ��β���
        // ����β���
        if( p->prior ){
            integer->tail = p->prior;
            p->prior->next = NULL;
            free(p);
            p = NULL;
            // ����ͷ�����������
            integer->head->num --;
            return;
        }else{  // p �ǹ���ͷ��㣬���������Ľ��
            integer->head = integer->tail = NULL;
            free(p);
            p = NULL;
            return;
        }

    }
    
    if( p->prior && p->next ){    // p ���м���
        p->prior->next = p->next;
        p->next->prior = p->prior;
        free(p);
        p = NULL;
        // ����ͷ�����������
        integer->head->num --;
        return;
    }

}

void DeleteInteger ( Integer* integer )
{
    // �� p ���� integer->tail����������ʱ�䣬�Կռ任ʱ��
    Number p = integer->tail;
    while( p ){
        DeleteNode( p, integer );
        p = integer->tail;
    }
}

Integer ReadInteger ( FILE* const fp )
{
    Integer integer;
    integer.head = integer.tail = NULL;
    char chr;
    int t;

    // ��ȡͷ�����ַ�
    // ���ݵ�һ���ַ� �ж���������������ͷ���
    // ���ݵڶ����ַ� ������һ������
    fscanf( fp, "%c", &chr );
    if( chr == '+' || chr == '0' ){
        // ��ȡ����ǰλ�� 0
        fscanf( fp, "%c", &chr );
        while( chr == '0' ){
            fscanf( fp, "%c", &chr );
        }
        // ����˵�һ����������
        t = (int)(chr-48);
        integer = CreateHead(1);
        TailAttch( t, &integer );
    }else if( chr == '-' ){
        // ��ȡ����ǰλ�� 0
        fscanf( fp, "%c", &chr );
        while( chr == '0' ){
            fscanf( fp, "%c", &chr );
        }
        // ����˵�һ����������
        t = (int)(chr-48);
        integer = CreateHead(-1);
        TailAttch( t, &integer );
    }else if( chr >= 49 && chr <= 57 ){ // chr ���յ���������
        t = (int)(chr-48);
        integer = CreateHead(1);
        TailAttch( t, &integer );
    }else{
        puts("Wrong input!");
        return integer;
    }

    
    fscanf( fp, "%c", &chr );
    while( chr != '\n' ){
        t = (int)(chr-48);
        TailAttch( t, &integer );
        fscanf( fp, "%c", &chr );
    }

    return integer;

}


Integer Multiply2Integer ( Integer* integer1, Integer* integer2 )
{
    Integer ret;
    ret.head = ret.tail = NULL;
    if( integer1->head->num == 0 || integer2->head->num == 0 ){
        ret = CreateHead(0);
        return ret;
    }
    /*ȥ�㣬����¼��Ŀ*/
    int num_of_tail_0 = 0;
    num_of_tail_0 = Throw0(integer1);
    num_of_tail_0 += Throw0(integer2);

    // �ñ���������Ѱַ
    int len1, len2;
    len1 = integer1->head->num;
    len2 = integer2->head->num;

    /*������ͷ*/
    if( len1 ^ len2 >= 0 ){// ͬ��
        ret = CreateHead(1);
    }else{
        ret = CreateHead(-1);
    }

    Number p1, p2, p3;
    p1 = integer1->tail;
    p2 = integer2->tail;
    int number;

    int loc=0, i, j;

    /*���˷�*/
    for( i=1; i < len2; i++ ){

        p1 = integer1->tail;
        p3 = ret.tail;
        for( j=0; j < loc; j++ ){
            p3 = p3->prior;
        }// �ƶ� p3��ָ���Ӧλ

        number = p2->num;

        for( j=1; j < len1; j++ ){
            if( p3 != ret.head ){// û��ͷ�����ֱ�Ӷ�Ӧ�ӵ������
                p3->num += p1->num*number;
                p3 = p3->prior;
            }else{// ��ͷ�ˣ������Ϊ�½�㣬���ӵ������
                HeadAttch( p1->num*number, &ret );
            }
            p1 = p1->prior;
        }

        loc ++;
        p2 = p2->prior;
    }
    /* ����ÿλ���ֿ��Դ洢�Ĵ�СΪ 2**32��ÿλ�洢 81��һλ���˷�����ÿλ�ϲ�����������֣�
    ���ս��Ҳ���Է��� 5 ǧ�����ϸ� 81 ��ӣ�Ҳ�������ٿ������� 5ǧ��λ �����˷�����ǧ���н�
    ����ӣ�Ҳ����ʹ�ý����������ֵĽ������������ο�ʵ���л��кܶಹ���� 0 λ�����Կ���
    ����ÿ�ζԽ����λ�淶��������������ܵĽ���Ͻ��г�ʼ�� */
    
    /*��λ�淶��*/
    CarryCanonicalize( &ret );
    /*����*/
    for( int i=0; i < num_of_tail_0; i++ ){
        TailAttch( 0, &ret );
    }

    return ret;
}

int Throw0 ( Integer *integer)
{
    Number p;
    p = integer->tail;
    int num_tail_0 = 0;

    while( p->num == 0 ){
        DeleteNode(p, integer);
        num_tail_0 ++;
        p = integer->tail;
    }

    return num_tail_0;
}

void CarryCanonicalize ( Integer* integer )
{
    Number p = integer->tail;
    while( p != integer->head->next ){
        if( p->num > 9 ){
            p->prior->num += p->num/10;
            p->num %= 10;
        }
        p = p->prior;
    }
    // ���Ͻ����½�㣬Ĩ����ǰ���� �����֣�0-9�������
    while( p->num > 9 ){
        HeadAttch( p->num/10, integer );
        p->num %= 10;
        p = p->prior;
    }

}

Integer DaShuJieCheng( int n )
{
    Integer ret;
    ret.head = ret.tail = NULL;
    ret = CreateHead(1);
    HeadAttch( 1, &ret );
    Number p;

    for( int i=2; i <= n; i++ ){
        p = ret.tail;
        for( int j=1; j < ret.head->num; j++ ){
            p->num *= i;
            p = p->prior;
        }
        CarryCanonicalize( &ret );
    }

    return ret;
}