# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define SIZE 6

enum Direction {up = 1, down = 2, left = 3, right = 4, null = 5};
typedef enum {available = 1, unavailable = 0} Block;
typedef Block** Field;
/* λ�� */
typedef struct {
    int x;
    int y;
} Location;
Location field_entrance = {1, 1}, field_exit = {4, 4};

/* ��� */
typedef struct {
    Location loc;       // ��¼�Լ���ǰ��λ��
    enum Direction nextBlock; // Ҫ�ߵķ���
} Player;
/* ջ */
typedef Player ElemType;
typedef struct _SNode{
    ElemType info;
    struct _SNode* next;
} SNode;
typedef SNode* Stack;

/* ջ�Ļ������� */
Stack CreateStack();
void Push(ElemType info, Stack s);
ElemType Pop(Stack s);
ElemType getTop(Stack s);
int getDeepth(Stack s);
void freeStack(Stack s);

/* ��ʼ���Թ� */
Field initField(int row, int col);
/* ��ұ����ĸ����򣬽�����һ������ */
void playerMove(Player* player, Field field, Stack route, Stack shortest);
/* ���·�� */
void printRoute(Stack route);
/* ��������·�� */
void printReversedRoute(Stack route);
/* ��¼���·�� */
void popAtoB(Stack A, Stack B);
/* ������һ������ */
void stepBack(Player* player, Stack route, Field field);


int main()
{
    Player player = {
        .loc = {field_entrance.x, field_entrance.y},
        .nextBlock = up
    };
    const Field field = initField(SIZE, SIZE);
    Stack route = CreateStack();
    Stack shortest = CreateStack();

    playerMove(&player, field, route, shortest);

    puts("���·����");
    printRoute(shortest);

    for (i = 0; i < col; i++) {
        free(field[i]);
    }
    free(field);
    freeStack(route);
    freeStack(shortest);

    system("pause");
    return 0;
}

Field initField(int row, int col)
{/* ��һά���� x �ᣨ���ᣩ���ڶ�ά���� y �ᣨ���ᣩ
  */
    int i;
    Field field = (Block**)malloc(col * sizeof(Block*));
    for (i = 0; i < col; i++) {
        field[i] = (Block*)malloc(row * sizeof(Block));
    }
    // ��ʼ���Թ�
    for (i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            field[i][j] = available;
        }
    }
    // ��ʼ���Թ���ǽ
    for (i = 0; i < row; i++) {
        field[0][i] = unavailable;
        field[col - 1][i] = unavailable;
    }
    for (i = 0; i < col; i++) {
        field[i][0] = unavailable;
        field[i][row - 1] = unavailable;
    }
    // ��ʼ�����ǽ
    field[1][4] = unavailable;
    field[2][2] = unavailable;
    field[4][3] = unavailable;
    field[4][1] = unavailable;

    return field;
}

void playerMove(Player* player, Field field, Stack route, Stack shortest)
{
    Location next_loc = {0, 0};
    // �������
    if ((player->loc.x == field_exit.x) && (player->loc.y == field_exit.y)) {
        printReversedRoute(route);
        if (getDeepth(route) < getDeepth(shortest) || getDeepth(shortest) == 0) {
            popAtoB(route, shortest);
        }
        stepBack(player, route, field);
        return;
    }
    // ��������
    while (true) {
        switch (player->nextBlock) {
        case up:
            next_loc.x = player->loc.x;
            next_loc.y = player->loc.y - 1;
            break;
        case down:
            next_loc.x = player->loc.x;
            next_loc.y = player->loc.y + 1;
            break;
        case left:
            next_loc.x = player->loc.x - 1;
            next_loc.y = player->loc.y;
            break;
        case right:
            next_loc.x = player->loc.x + 1;
            next_loc.y = player->loc.y;
            break;
        default:
            // ��·����
            if (route->next) {
                stepBack(player, route, field);
            }
            return;
            break;
        }
        // �ɴ�����¸����
        if (field[next_loc.x][next_loc.y] == available) {
            Push(*player, route);
            field[player->loc.x][player->loc.y] = unavailable;
            player->loc = next_loc;
            player->nextBlock = up;
            playerMove(player, field, route, shortest);
        }
        // �鿴�¸�����
        player->nextBlock++;
    }

}

void printRoute(Stack route)
{
    SNode* p = route->next;
    while (p) {
        printf("(%d, %d)->", p->info.loc.x, p->info.loc.y);
        p = p->next;
    }
    printf("Exit: (%d, %d)\n", field_exit.x, field_exit.y);
}

void printReversedRoute(Stack route)
{
    SNode* p = route->next;
    static int cnt = 0;
    if (p) {
        cnt++;
        printReversedRoute(p);
        cnt--;
        printf("(%d, %d)->", p->info.loc.x, p->info.loc.y);
        if (cnt == 0) {
            printf("Exit: (%d, %d)\n", field_exit.x, field_exit.y);
        }
    }
}

void popAtoB(Stack A, Stack B)
{
    SNode* p = B->next;
    SNode* q = A->next;
    // ���
    while (p) {
        Pop(B);
    }
    // ��¼
    while (q) {
        Push(q->info, B);
        q = q->next;
    }
}

void stepBack(Player* player, Stack route, Field field)
{
    Player last_info = Pop(route);
    // �������ˣ����õ�ǰ���ɴ�
    field[player->loc.x][player->loc.y] = available;
    *player = last_info;
}
/*********************************************************************************/
Stack CreateStack()
{
    Stack s = (Stack)malloc(sizeof(SNode));
    s->next = NULL;
    return s;
}

void Push(ElemType info, Stack s)
{
    Stack temp = (Stack)malloc(sizeof(SNode));
    temp->info = info;
    temp->next = s->next;
    s->next = temp;
}

ElemType Pop(Stack s)
{
    SNode* p;
    ElemType info = {.loc = {0, 0}, .nextBlock = 0};
    
    if (s->next == NULL) {
        printf("The stack is empty!");
    } else {
        p = s->next;
        info = p->info;
        s->next = p->next;
        free(p);
    }
    
    return info;
}

ElemType getTop(Stack s)
{
    ElemType top_info = {.loc = {0, 0}, .nextBlock = 0};
    if (s->next) {
        top_info = s->next->info;
    }
    return top_info;
}

int getDeepth(Stack s)
{
    int deepth = 0;
    SNode* p = s->next;
    while (p) {
        deepth++;
        p = p->next;
    }
    return deepth;
}

void freeStack(Stack s)
{
    SNode* p = s->next;
    while (p) {
        s->next = p->next;
        free(p);
        p = s->next;
    }
    free(s);
    s = NULL;
}