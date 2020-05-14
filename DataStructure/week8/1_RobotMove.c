# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define ROW 2
# define COL 5

typedef struct {
    int x;
    int y;
} Location;

typedef Location ElemType;
typedef struct {
    ElemType* route;
    int size;
    int sp;
} stack_block;
typedef stack_block* Stack;

Stack creatStack_size(int size);
bool push(Stack s, ElemType elem);
ElemType pop(Stack s);
void destroyStack(Stack s);
void printStack(Stack s);

int move(int** map, Location loc, const Location exit, Stack route)
{
    int cnt = 0;

    if (loc.x == exit.x && loc.y == exit.y) {
        printStack(route);
        printf("(%d, %d)\n", loc.x, loc.y);
        return 1;
    }

    // turn left
    if (loc.x > exit.x) {
        push(route, loc);
        loc.x--;
        cnt += move(map, loc, exit, route);
        loc = pop(route);
    }
    // turn up
    if (loc.y > exit.y) {
        push(route, loc);
        loc.y--;
        cnt += move(map, loc, exit, route);
        loc = pop(route);
    }

}

int main()
{
    int** map = (int**)malloc(sizeof(int*) * (ROW + 1));

    for (int i = 0; i < ROW + 1; i++) {
        map[i] = (int*)malloc(sizeof(int) * (COL + 1));
    }

    Location entrance = {.x = 5, .y = 2};
    Location exit = {.x = 1, .y = 1};
    Stack route = creatStack_size(entrance.x - exit.x + entrance.y - exit.y);

    move(map, entrance, exit, route);

    for (int i = 0; i < ROW + 1; i++) {
        free(map[i]);
    }
    free(map);
    destroyStack(route);

    system("pause");
    return 0;
}


Stack creatStack_size(int size)
{
    Stack s = (Stack)malloc(sizeof(stack_block));
    s->route = NULL;
    s->size = 0;
    s->sp = -1;
    if (size > 0) {
        s->size = size;
        s->route = (Location*)malloc(sizeof(ElemType) * size);
    }
}

bool push(Stack s, ElemType elem)
{
    bool is_full = false;

    if (s->sp == s->size - 1) {
        is_full = true;
    } else {
        s->route[++s->sp] = elem;
    }

    return is_full;
}

ElemType pop(Stack s)
{
    ElemType top_elem = {.x = 0, .y = 0};

    if (s->sp > -1) {
        top_elem = s->route[s->sp--];
    }

    return top_elem;
}

void destroyStack(Stack s)
{
    free(s->route);
    free(s);
    s = NULL;
}

void printStack(Stack s)
{
    for (int i = 0; i <= s->sp; i++) {
        printf("(%d, %d) -> ", s->route[i].y, s->route[i].x);
    }
}