#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType* base;
    ElemType* top;
    int stackSize;
}SqStack;

Status InitStack(SqStack* S)
{
    S->base=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stackSize=MAXSIZE;
    return OK;
}

Status StackEmpty(SqStack S)
{
    return (S.base==S.top)?TRUE:FALSE;
}

int StackLength(SqStack S)
{
    return S.top-S.base;
}

Status ClearStack(SqStack* S)
{
    if(S->base)
    S->top=S->base;
    return OK;
}

Status DestroyStack(SqStack* S)
{
    if(S->base)
    {
        free(S->base);
        S->base=NULL;
        S->top=NULL;
        S->stackSize=0;
    }
    return OK;
}

Status Push(SqStack* S,ElemType e)
{
    if(S->top-S->base==S->stackSize) return ERROR;
    *S->top++=e;
    return OK;
}

Status Pop(SqStack* S,ElemType* e)
{
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}

Status GetTop(SqStack S,ElemType* e)
{
    if(StackEmpty(S)) return ERROR;
    *e=*(S.top-1);
    return OK;
}

void StackTraverse(const SqStack *S)
{
    ElemType* p=S->base;
    while(p!=S->top)
    {
        printf("%d ",*p);
        p++;
    }
    printf("\n");
}

int main()
{
    SqStack S;
    ElemType e;

    InitStack(&S);

    Push(&S,1);
    Push(&S,2);
    Push(&S,3);

    StackTraverse(&S);

    Pop(&S,&e);

    printf("length=%d\n",StackLength(S));

    ClearStack(&S);
    printf("栈是否为空：%s\n",StackEmpty(S)?"是":"否");

    DestroyStack(&S);

    return OK;
}