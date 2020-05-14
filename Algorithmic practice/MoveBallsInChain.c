# include <stdio.h>
# include <stdlib.h>

typedef struct _ball{
    int num;
    struct _ball* next;
    struct _ball* prior;
} Ball;

typedef struct {
    Ball* head;
    Ball* tail;
} BallList;

/* 生成初始球链 */
BallList CreatInitBalls ( int size );
/* 生成一个小球 */
Ball* MakeOneBall ( int num );
/* 改变小球排序 */
void ChangeOrder ( char command, int num1, int num2, BallList* balls );
/* 找到对应序号的小球，返回地址 */
Ball* FindBall ( int num, Ball* head );
/* 输出球链 */
void OutputBallList ( Ball* head );
/* 释放球链 */
void DeleteBallList ( BallList* balls );


int main()
{
    int size, cmd_num;
    char command;
    int num1, num2;

    FILE* fp = fopen("D:\\VS Code\\C\\Algorithmic practice\\week10.txt", "r");
    if(fp){
        fscanf(fp, "%d%d\n", &size, &cmd_num);
        BallList balls = CreatInitBalls(size);
        for( int i=0; i<cmd_num; i++ ){
            fscanf(fp, "%c%d%d\n", &command, &num1, &num2);
            ChangeOrder(command, num1, num2, &balls);
        }
        OutputBallList(balls.head);
        DeleteBallList(&balls);
    }else{
        printf("Can't open the file.\n");
    }

    system("pause");
    return 0;
}

BallList CreatInitBalls ( int size )
{
    BallList balls = {.head = NULL, .tail = NULL};
    balls.head = balls.tail = MakeOneBall(0);

    Ball* temp;
    for( int i=1; i <= size; i++ ){
        temp = MakeOneBall(i);
        balls.tail->next = temp;
        temp->prior = balls.tail;
        balls.tail = balls.tail->next;
    }

    return balls;    
}

Ball* MakeOneBall ( int num )
{
    Ball* p;
    p = (Ball*)malloc(sizeof(Ball));
    p->num = num;
    p->next = p->prior = NULL;

    return p;
}

void ChangeOrder ( char command, int num1, int num2, BallList* balls )
{
    Ball* ptr1,* ptr2;

    if( num1 ^ num2 ){
        // 找出对应序号小球地址
        ptr1 = FindBall(num1, balls->head);
        ptr2 = FindBall(num2, balls->head);
        // 取出 ptr1
        if(ptr1->next){
            ptr1->prior->next = ptr1->next;
            ptr1->next->prior = ptr1->prior;
        }else{
            ptr1->prior->next = NULL;
        }
        // 操作指令
        if(command == 'L'){
            // 在 ptr2 左端插入 ptr1
            ptr2->prior->next = ptr1;
            ptr1->prior = ptr2->prior;
            ptr2->prior = ptr1;
            ptr1->next = ptr2;
        }else if(command == 'R'){
            // 在 ptr2 右端插入 ptr1
            if(ptr2->next){
                ptr2->next->prior = ptr1;
                ptr1->next = ptr2->next;
                ptr2->next = ptr1;
                ptr1->prior = ptr2;
            }else{
                ptr2->next = ptr1;
                ptr1->prior = ptr2;
                ptr1->next = NULL;
            }
        }
    }
}

Ball* FindBall ( int num, Ball* head )
{
    Ball* p = head;
    while( p->num ^ num ){
        p = p->next;
    }
    return p;
}

void DeleteBallList ( BallList* balls )
{
    Ball* p = balls->tail;
    while(p){
        p = p->prior;
        free(balls->tail);
        balls->tail = p;
    }
    balls->head = balls->tail = NULL;
}

void OutputBallList ( Ball* head )
{
    Ball* p = head->next;
    while(p){
        printf("%d ", p->num);
        p = p->next;
    }
    putchar('\n');
}