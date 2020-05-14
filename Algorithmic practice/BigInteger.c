# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define ABS(x) ( ((x)>0) ? (x) : (-1*(x)) )

clock_t start, stop;
double duration;

/* READ ME：
1、 大数运算时从后向前运算，运算结果是末位，需要存放末位
    输入数据时又需要先存放首位
    则对于 TailAttch 无法统一
    除非对运算链使用堆栈结构，对结果链使用队列结构，这样又无法统一数据结构
    只好构造两种 TailAttch，一个从前向后，一个从后向前
*/

typedef struct _NumberNode* Number;
typedef struct _NumberNode{
    int num;
    Number next;
    Number prior;
} NumberNode;

// Integer 类型存放数字链的头尾指针
typedef struct {
    Number head;
    Number tail;
} Integer;



/* 建立一个头结点 */
Integer CreateHead ( int sign );
/* 从头结点连接上新元素 */
void TailAttch ( int number, Integer* integer );
/* 从尾结点连接上新元素 */
void HeadAttch ( int number, Integer* integer );
/* 输入一个大数 */
Integer InputInteger ( void ); //  调用 CreateHead 和 TailAttch 函数
/* 输出一个大数 */
void OutputInteger ( Number p );
/* 两个大数相加 */
Integer Add2Integer ( Integer* integer1, Integer* integer2 );
/* 同号和 */
Integer PPorNN_Add ( Integer* integer1, Integer* integer2 );
/* 异号和 */
Integer PN_Add ( Integer* integer1, Integer* integer2 );
/* 比较大小 */
int Compare2Integer_Abs ( Number head1, Number head2 );

/* 删除一个数字结点 */
void DeleteNode ( Number p, Integer* integer );
/* 删除整个整数链 */
void DeleteInteger ( Integer* integer );

/* 从文件读入一个大数 */
Integer ReadInteger ( FILE* const fp );

/* 两个大数相乘 */
Integer Multiply2Integer ( Integer* integer1, Integer* integer2 );
/* 进位规范化 */
void CarryCanonicalize ( Integer* integer );//可能需要改变链头，故要传指针
/* 去零函数，返回去掉的零数 */
int Throw0 ( Integer *integer);

Integer DaShuJieCheng( int n );// 这个 n不应大于 2**32-2**32/10 至 2**32/9 之间的某个数，数十亿的量级

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
    1、建立头结点，实现整数的正负表示，1表正数 -1表负数 0表空数链
    2、头结点还存放链长，正数链增加结点，则头结点 num++，负数链增加结点，则头结点 num--
    */
    Integer new_integer;
    new_integer.head = new_integer.tail = (Number)malloc(sizeof(NumberNode));
    new_integer.head->num = sign;
    new_integer.head->next = new_integer.head->prior = NULL;

    return new_integer;
}

void TailAttch ( int number, Integer* integer )
{
    // 构造新结点
    Number new_num;
    new_num = (Number)malloc(sizeof(NumberNode));
    new_num->num = number;
    // 连接新结点
    new_num->prior = integer->tail;
    new_num->next = NULL;
    new_num->prior->next = new_num;
    // 重定位尾指针
    integer->tail = new_num;

    // 更新链长
    if( integer->head->num > 0 ){
        integer->head->num++;
    }else if( integer->head->num < 0 ){
        integer->head->num--;
    }
}
void HeadAttch ( int number, Integer* integer )
{
    // 构造新结点
    Number new_num;
    new_num = (Number)malloc(sizeof(NumberNode));
    new_num->num = number;
    new_num->next = NULL;
    // 连接新结点
    if(integer->head->next){
    // 头结点之后有结点
        // 连接新结点
        new_num->prior = integer->head;
        new_num->next = integer->head->next;
        integer->head->next = new_num;
        new_num->next->prior = new_num;
    }else{
    // 仅头结点
        // 连接新结点
        new_num->prior = integer->head;
        new_num->next = integer->head->next;
        integer->head->next = new_num;
        // 重定位尾指针
        integer->tail = new_num;
    }

    // 更新链长
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
    // 先读第一个
    scanf("%c", &sgn);
    
    // 判断数字正负，建立头结点 以及 第一个数字
    if( sgn == '+' || sgn == '0' ){
        while( (sgn = getchar()) == '0' ){}   // 截取所有前位的 0
        // 获得第一个非零数字
        t = (int)(sgn-48);
        integer = CreateHead(1);
        TailAttch( t, &integer );
    }else if( sgn == '-' ){
        while( (sgn = getchar()) == '0' ){}   // 截取所有前位的 0
        // 获得第一个非零数字
        t = (int)(sgn-48);
        integer = CreateHead(-1);
        TailAttch( t, &integer );
    }else if( sgn >= 49 && sgn <= 57 ){ // sgn 接收到的是数字
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

    return integer; // 返回，大数链表的头尾信息 integer

}

void OutputInteger ( Number p )
{
    // 先输出正负信息
    if( p->num < 0 ){
        // 头结点数据小于 0，负数
        putchar('-');
    }else if( p->num == 0 ){
        // 头结点数据为 0，数为 0
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
    1、先判断两个数的正负，来决定使用那种运算
        # 同号则继承符号，然后相加
        # 异号则先比绝对大小
            $ 先比链长
            $ 链等则一位一位比较
          保证是大的减小的，然后符号随大的
    2、运算时，先直接从后向前运算每个结点
       存放到结果链，再进行 “规范化”
        # 相加的规范化需要进行进位处理
        # 相减的规范化需要进行借位处理
        # 相减规范化还需要对相加出来的前位 0 的删除
    */
    Integer ret;
    ret.head = ret.tail = NULL;

    if( (integer1->head->num ^ integer2->head->num) >= 0 ){
    // 包括 同号相加、正数+0、0+0
        ret = PPorNN_Add( integer1, integer2 );
    }else{
    // 包括 异号相加、负数+0
        switch ( Compare2Integer_Abs( integer1->head, integer2->head ) ){
        case 1:
            ret = PN_Add( integer1, integer2 );
            break;
        case -1:
            ret = PN_Add( integer2, integer1 );
            break;
        default:    // 两者完全相等
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

    // 赋予整数链 正负信息
    if( integer1->head->num > 0 ){
        ret = CreateHead(1);
    }else if( integer1->head->num < 0 ){
        ret = CreateHead(-1);
    }else{  // integer1 是空链，再对 integer2 判断
        if( integer2->head->num == 0 ){
            // 两个都是 0，不用运算，直接返回
            return *integer1;
        }else{
            // integer2 非 0，直接返回 integer2 作为结果
            return *integer2;
        }
    }

    // 直接从后向前相加
    while( (p1 != integer1->head) && (p2 != integer2->head) ){
        HeadAttch( p1->num + p2->num, &ret );
        p1 = p1->prior;
        p2 = p2->prior;
    }
    // 有一个指针 “触头”了
    while( p1 != integer1->head ){
        HeadAttch( p1->num, &ret );
        p1 = p1->prior;

    }
    while( p2 != integer2->head ){
        HeadAttch( p2->num, &ret );
        p2 = p2->prior;
    }

    /* 进位规范化 */
    // 加法时进位最大只会进位 1位，不需要考虑乘法那样
    Number p3 = ret.tail;
    while( p3 != ret.head->next ){
        if( p3->num > 9 ){
            p3->num %= 10;
            p3->prior->num ++;
        }
        p3 = p3->prior;
    }
    // p3 到达头结点前一位，即整数的第一位
    if( p3->num > 9 ){
        p3->num %= 10;
        // 在头结点后增加一个数字结点
        HeadAttch( 1, &ret );
    }

    return ret;
}

Integer PN_Add ( Integer* integer1, Integer* integer2 )
{
    // 传入的时候，关于绝对值，前者大于后者

    Integer ret;
    ret.head = ret.tail = NULL;
    Number p1, p2;
    p1 = integer1->tail;
    p2 = integer2->tail;

    // 赋予整数链 正负信息
    ret = CreateHead(integer1->head->num/ABS(integer1->head->num));
    // 直接从后向前相减
    while( p2 != integer2->head ){
        HeadAttch( p1->num - p2->num, &ret );
        p1 = p1->prior;
        p2 = p2->prior;
    }
    // p2 “触头”了
    while( p1 != integer1->head ){
        HeadAttch( p1->num, &ret );
        p1 = p1->prior;
    }

    /* 借位规范化 */
    Number p3 = ret.tail;
    while( p3 != ret.head->next ){
        if( p3->num < 0 ){
            p3->num += 10;
            p3->prior->num --;
        }
        p3 = p3->prior;
    }
    // 由于是大数减小数，所以只需要考虑整数头一位是否是 0（降位的情况），是则去除掉
    // p3 到达头结点前一位，即整数的第一位
    if( p3->num == 0 ){
        DeleteNode( p3, &ret );
    }

    return ret;
}

int Compare2Integer_Abs ( Number head1, Number head2 )
{
    // 大于返回 1，小于返回 -1，相等返回 0

    int ret;

    if( ABS(head1->num) > ABS(head2->num) ){
        ret = 1;
    }else if( ABS(head1->num) < ABS(head2->num) ){
        ret = -1;
    }else{  // 链表等长，比各位数字大小
        head1 = head1->next;
        head2 = head2->next;
        while( head1 ){    // 但两者等长，故用其中一个代替
            if( head1->num > head2->num ){
                ret = 1;
                break;  // 比出大小了，退出循环
            }else if( head1->num < head2->num ){
                ret = -1;
                break;  // 比出大小了，退出循环
            }else{
                // 没比出大小，移位继续
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
    /*  删除中间结点的情况，一般较少，只如减法出现退位
        调用的情况最可能的是当要删除整个整数链的时候
        删除整个整数链的时候，从尾巴开始，删到头结点(当作尾结点删除)，不涉及中间结点
        故把尾结点判断放在最前面，其次才是中间结点 */

    if( p == integer->tail ){    // p 是尾结点
        // 更新尾结点
        if( p->prior ){
            integer->tail = p->prior;
            p->prior->next = NULL;
            free(p);
            p = NULL;
            // 更新头结点链长数据
            integer->head->num --;
            return;
        }else{  // p 是孤立头结点，即链中最后的结点
            integer->head = integer->tail = NULL;
            free(p);
            p = NULL;
            return;
        }

    }
    
    if( p->prior && p->next ){    // p 是中间结点
        p->prior->next = p->next;
        p->next->prior = p->prior;
        free(p);
        p = NULL;
        // 更新头结点链长数据
        integer->head->num --;
        return;
    }

}

void DeleteInteger ( Integer* integer )
{
    // 用 p 代表 integer->tail，减少运算时间，以空间换时间
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

    // 读取头两个字符
    // 根据第一个字符 判断数字正负，建立头结点
    // 根据第二个字符 建立第一个数字
    fscanf( fp, "%c", &chr );
    if( chr == '+' || chr == '0' ){
        // 截取所有前位的 0
        fscanf( fp, "%c", &chr );
        while( chr == '0' ){
            fscanf( fp, "%c", &chr );
        }
        // 获得了第一个非零数字
        t = (int)(chr-48);
        integer = CreateHead(1);
        TailAttch( t, &integer );
    }else if( chr == '-' ){
        // 截取所有前位的 0
        fscanf( fp, "%c", &chr );
        while( chr == '0' ){
            fscanf( fp, "%c", &chr );
        }
        // 获得了第一个非零数字
        t = (int)(chr-48);
        integer = CreateHead(-1);
        TailAttch( t, &integer );
    }else if( chr >= 49 && chr <= 57 ){ // chr 接收到的是数字
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
    /*去零，并记录数目*/
    int num_of_tail_0 = 0;
    num_of_tail_0 = Throw0(integer1);
    num_of_tail_0 += Throw0(integer2);

    // 用变量替代多次寻址
    int len1, len2;
    len1 = integer1->head->num;
    len2 = integer2->head->num;

    /*建立链头*/
    if( len1 ^ len2 >= 0 ){// 同号
        ret = CreateHead(1);
    }else{
        ret = CreateHead(-1);
    }

    Number p1, p2, p3;
    p1 = integer1->tail;
    p2 = integer2->tail;
    int number;

    int loc=0, i, j;

    /*拆解乘法*/
    for( i=1; i < len2; i++ ){

        p1 = integer1->tail;
        p3 = ret.tail;
        for( j=0; j < loc; j++ ){
            p3 = p3->prior;
        }// 移动 p3，指向对应位

        number = p2->num;

        for( j=1; j < len1; j++ ){
            if( p3 != ret.head ){// 没触头，结果直接对应加到结果链
                p3->num += p1->num*number;
                p3 = p3->prior;
            }else{// 触头了，结果作为新结点，连接到结果链
                HeadAttch( p1->num*number, &ret );
            }
            p1 = p1->prior;
        }

        loc ++;
        p2 = p2->prior;
    }
    /* 由于每位数字可以存储的大小为 2**32，每位存储 81（一位数乘法能在每位上产生的最大数字）
    最终结果也足以放下 5 千万以上个 81 相加，也就是至少可以满足 5千万位 大数乘法（五千万行结
    果相加，也不会使得结果链存放数字的结点溢出），更何况实际中会有很多补零后的 0 位，所以可以
    不用每次对结果进位规范化，而是在最后总的结果上进行初始化 */
    
    /*进位规范化*/
    CarryCanonicalize( &ret );
    /*补零*/
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
    // 不断建立新结点，抹匀最前结点的 “数字（0-9）溢出”
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