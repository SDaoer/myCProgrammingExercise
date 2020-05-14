# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAXSIZE 10
# define ERROR 0

typedef int ElemType;
typedef struct _QNode{
    ElemType data[MAXSIZE];
    int len;
    int rear;
} QNode;
typedef QNode* Queue;

void initQueue(Queue q)
{
    q->len = 0;
    q->rear = -1;
}

void AddToQueue( Queue PtrQ, ElemType item )
{
    if (PtrQ->len == MAXSIZE) {
        printf("The queue is full!\n");
        return;
    } else {
        PtrQ->rear = (PtrQ->rear+1) % MAXSIZE;
        PtrQ->data[PtrQ->rear] = item;
        PtrQ->len++;
    }
}

ElemType DeleteFromQueue( Queue PtrQ )
{
    if (PtrQ->len == 0) {
        printf("The queue is empty!\n");
        return ERROR;
    } else {
        return PtrQ->data[(PtrQ->rear + 1 - (PtrQ->len--) + MAXSIZE) % MAXSIZE];
    }
}

bool queueEmpty(Queue q)
{
    return (q->len == 0);
}

int main()
{
    Queue q = (Queue)malloc(sizeof(QNode));
    initQueue(q);
    AddToQueue(q, 1);
    AddToQueue(q, 3);
    AddToQueue(q, 2);
    printf("%d ", DeleteFromQueue(q));
    printf("%d ", DeleteFromQueue(q));
    printf("%d ", DeleteFromQueue(q));

    putchar('\n');

    free(q);

    system("pause");
    return 0;
}