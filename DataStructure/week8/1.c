# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define ROW 2
# define COL 5

enum Direction {up = 1, left = 2, null = 3};
typedef enum {available = 1, unavailable = 0} Block;
typedef Block** Field;
/* λ�� */
typedef struct {
    int x;
    int y;
} Location;
Location field_entrance = {2, 5}, field_exit = {1, 1};

/* ��� */
typedef struct {
    Location loc;       // ��¼�Լ���ǰ��λ��
    enum Direction nextBlock; // Ҫ�ߵķ���
} Player;
/* ջ */
typedef Player ElemType;
typedef struct _SNode {
    ElemType info;
    struct _SNode* next;
} SNode;
typedef SNode* Stack;

/* ջ�Ļ������� */
Stack CreateStack();
void Push(ElemType info, Stack s);
ElemType Pop(Stack s);
void freeStack(Stack s);

/* ��ʼ���Թ� */
Field initField(int row, int col);
/* ��ұ����ĸ����򣬽�����һ������ */
void playerMove(Player* player, Field field, Stack route);
/* ������һ������ */
void stepBack(Player* player, Stack route, Field field);
/* ��������·�� */
void printReversedRoute(Stack route);


int main()
{
    Player player = {
        .loc = {field_entrance.x, field_entrance.y},
        .nextBlock = up
    };
    const Field field = initField(ROW + 2, COL + 2);
    Stack route = CreateStack();

    playerMove(&player, field, route);

    freeStack(route);

    system("pause");
    return 0;
}

Field initField(int row, int col)
{
    int i;
    Field field = (Block**)malloc(row * sizeof(Block*));
    for (i = 0; i < col; i++) {
        field[i] = (Block*)malloc(col * sizeof(Block));
    }
    // ��ʼ���Թ�
    for (i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            field[i][j] = available;
        }
    }
    // ��ʼ���Թ���ǽ
    for (i = 0; i < row; i++) {
        field[i][0] = unavailable;
        field[i][col - 1] = unavailable;
    }
    for (i = 0; i < col; i++) {
        field[0][i] = unavailable;
        field[row - 1][i] = unavailable;
    }

    return field;
}

void playerMove(Player* player, Field field, Stack route)
{
    Location next_loc = {0, 0};
    // �������
    if ((player->loc.x == field_exit.x) && (player->loc.y == field_exit.y)) {
        printReversedRoute(route);
        stepBack(player, route, field);
        return;
    }
    // ��������
    while (player->nextBlock != null) {
        switch (player->nextBlock) {
        case up:
            next_loc.x = player->loc.x - 1;
            next_loc.y = player->loc.y;
            break;
        case left:
            next_loc.x = player->loc.x;
            next_loc.y = player->loc.y - 1;
            break;
        default:
            break;
        }
        // �ɴ�����¸����
        if (field[next_loc.x][next_loc.y] == available) {
            Push(*player, route);
            field[player->loc.x][player->loc.y] = unavailable;
            player->loc = next_loc;
            player->nextBlock = up;
            playerMove(player, field, route);
        }
        // �鿴�¸�����
        player->nextBlock++;
    }

    // ��·����
    if (route->next) {
        stepBack(player, route, field);
    }
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