#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType;

typedef struct StackNode
{
    SElemType data;
    struct StackNode* next;
}StackNode,*LinkStack;

Status InitStack(LinkStack* S)
{
    *S=NULL;
    return OK;
}

Status StackEmpty(LinkStack S)
{
    return (S==NULL)?TRUE:FALSE;
}

Status Push(LinkStack* S,SElemType e)
{
    LinkStack p=(LinkStack)malloc(sizeof(StackNode));
    if(!p) return ERROR;
    p->data=e;
    p->next=*S;
    *S=p;
    return OK;
}

Status Pop(LinkStack* S,SElemType* e)
{
    if(*S==NULL) return ERROR;
    LinkStack p=*S;
    *e=p->data;
    *S=p->next;
    free(p);
    return OK;
}

Status GetTop(LinkStack S,SElemType* e)
{
    if(S==NULL) return ERROR;
    *e=S->data;
    return OK;
}

void StackTravse(LinkStack S)
{
    LinkStack p=S;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

Status DestroyStack(LinkStack* S)
{
    LinkStack p,q;
    p=*S;
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    *S=NULL;
    return OK;
}

int main()
{
    LinkStack S;
    SElemType e;
    InitStack(&S);
    Push(&S,1);
    Push(&S,2);
    Push(&S,3);

    StackTravse(S);

    GetTop(S,&e);
    printf("%d\n",e);

    Pop(&S,&e);
    StackTravse(S);
    printf("栈是否为空：%s\n",StackEmpty(S)?"是":"否");
    DestroyStack(&S);
    printf("栈是否为空：%s\n",StackEmpty(S)?"是":"否");

    return 0;
}