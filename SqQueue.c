#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int QElemType;
typedef int Status;

typedef struct
{
	QElemType* base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(sizeof(QElemType)*MAXSIZE);
	if (!Q->base) exit(OVERFLOW);
	Q->front = Q->rear = 0;
	return OK;
}

int QueueLength(SqQueue Q)
{
	return((Q.rear - Q.front + MAXSIZE) % MAXSIZE);
}

Status EnQueue(SqQueue* Q,QElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front) return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (Q->front == Q->rear) return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

Status GetHead(SqQueue Q,QElemType* e)
{
	if (Q.rear == Q.front) return ERROR;
	*e =Q.base[Q.front];
    return OK;
}

int main()
{
    SqQueue Q;
    QElemType e;

    InitQueue(&Q);

    EnQueue(&Q,1);
    EnQueue(&Q,2);
    EnQueue(&Q,3);

    printf("Length=%d\n",QueueLength(Q));

    GetHead(Q,&e);
    printf("%d\n",e);

    DeQueue(&Q,&e);
    printf("Length=%d\n",QueueLength(Q));

    return 0;
}