# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

# define OP_NUM 8
# define A_LIM 3
# define B_LIM 5

/*******************************************************
两水杯，有各自的容量，仅有三种操作
1）把水倒空
2）把水接满
3）把一个杯子的水倒入另一个杯子，原杯子倒空，或者倒入的被子满

要求获得某固定数量的水
*******************************************************/

bool StateChart[A_LIM][B_LIM] = {0};
char Operate[OP_NUM][30] = {
    {"Empty A"},  {"Empty B"},  {"Full A"},  {"Full B"}, 
    {"Pour A to B until A is empty"}, {"Pour B to A until B is empty"}, 
    {"Pour A to B until B is full"}, {"Pour B to A until A is full"}
};

typedef struct _glass{
    int limit;
    int contain;
} Glass;

typedef struct _node{
    int x;
    int y;
    int op;/* 1~8，对应不同操作的描述，0不对应任何操作 */
    struct _node* next[OP_NUM];
} Node;

typedef Node* Tree;

Tree CreatTree ( Glass* A, Glass* B );


bool EmptyFirstGlass ( Glass* glass1, Glass* glass2 );
bool FullFirstGlass ( Glass* glass1, Glass* glass2 );
bool PourUntilEmptyFirstGlass ( Glass* glass1, Glass* glass2 );
bool PourUntilFullSecondGlass ( Glass* glass1, Glass* glass2 );
bool (*OP[OP_NUM/2]) ( Glass* glass1, Glass* glass2 ) = {
    EmptyFirstGlass, FullFirstGlass, PourUntilEmptyFirstGlass, PourUntilFullSecondGlass
};

int main()
{
    Glass A = {.limit=A_LIM, .contain=0}, B = {.limit=B_LIM, .contain=0};


    
    system("pause");
    return 0;
}

bool EmptyFirstGlass ( Glass* glass1, Glass* glass2 )
{
    bool operated = false;

    Glass temp = *glass1;
    temp.contain = 0;

    if( StateChart[temp.contain][glass2->contain] == false ){
        glass1->contain = 0;
        operated = true;
    }

    return operated;
}

bool FullFirstGlass ( Glass* glass1, Glass* glass2 )
{
    bool operated = false;

    Glass temp = *glass1;
    temp.contain = 0;

    if( StateChart[temp.contain][glass2->contain] == false ){
        glass1->contain = glass1->limit;
        operated = true;
    }

    return operated;

}

bool PourUntilEmptyFirstGlass ( Glass* glass1, Glass* glass2 )
{
    bool operated = false;

    Glass temp1 = *glass1, temp2 = *glass2;
    if( temp1.contain >= (temp2.limit-temp2.contain) ){
        temp2.contain = temp2.limit;
        temp1.contain = 0;
    }else{
        temp2.contain += temp1.contain;
        temp1.contain = 0;
    }
    if( StateChart[temp1.contain][temp2.contain] == false ){
        *glass1 = temp1;
        *glass2 = temp2;
        operated = true;
    }

    return operated;
}

bool PourUntilFullSecondGlass ( Glass* glass1, Glass* glass2 )
{
    bool operated = false;

    Glass temp1 = *glass1, temp2 = *glass2;
    if( temp1.contain >= (temp2.limit-temp2.contain) ){
        temp2.contain = temp2.limit;
        temp1.contain -= (temp2.limit-temp2.contain);
    }else{
        temp2.contain += temp1.contain;
        temp1.contain = 0;
    }
    if( StateChart[temp1.contain][temp2.contain] == false ){
        *glass1 = temp1;
        *glass2 = temp2;
        operated = true;
    }

    return operated;
}

Node* MakeNode ( int x, int y, int op )
{
    Node* node;
    node = (Node*)malloc(sizeof(Node));
    node->x = x;
    node->y = y;
    node->op = op;
    for( int i=0; i < OP_NUM; i++ ){
        node->next[i] = NULL;
    }

    return node;
}

Tree CreatTree ( Glass* A, Glass* B )
{
    Tree rootNode;
    rootNode = MakeNode(0, 0, 0);
    StateChart[0][0] = 1;

    Glass temp;

    for( int i=0; i < OP_NUM/2; i++ ){
        OP[i](Glass)
    }



    return rootNode;
}