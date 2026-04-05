#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct Node
{
    ElemType data;
    struct Node* next;
}Node,*LinkList;

Status InitList(LinkList* L)
{
    *L=(LinkList)malloc(sizeof(Node));
    if(!(*L)) return ERROR;
    (*L)->next=NULL;
    return OK;
}

Status ListEmpty(LinkList L)
{
    if(L->next) return FALSE;
    else return TRUE;
}

Status DestroyList(LinkList* L)
{
    LinkList p;
    while(*L)
    {
        p=*L;
        *L=(*L)->next;
        free(p);
    }
    return OK;
}

Status ClearList(LinkList* L)
{
    LinkList p,q;
    p=(*L)->next;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;
    return OK;
}

int ListLength(LinkList L)
{
    LinkList p=L->next;
    int i=0;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

Status GetElem(LinkList L,int i,ElemType* e)
{
    LinkList p=L->next;
    int j=1;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i) return ERROR;
    *e=p->data;
    return OK;
}

int LocateElem(LinkList L,ElemType e)
{
    LinkList p=L->next;
    int i=1;
    while(p&&p->data!=e)
    {
        p=p->next;
        i++;
    }
    if(p) return i;
    else return 0;
}

Status ListInsert(LinkList* L,int i,ElemType e)
{
    int j=0;
    LinkList p,s;
    p=*L;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1) return ERROR;
    s=(LinkList)malloc(sizeof(Node));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}

Status ListDelete(LinkList* L,int i,ElemType* e)
{
    LinkList p,q;
    p=(*L);
    int j=0;
    while(p->next&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!(p->next)||j>i-1) return ERROR;
    q=p->next;
    p->next=q->next;
    *e=q->data;
    free(q);
    return OK;
}

void CreateList_H(LinkList* L,int n)
{
    LinkList p;
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
    for(int i=n;i>0;i--)
    {
        p=(LinkList)malloc(sizeof(Node));
        scanf("%d",&p->data);
        p->next=(*L)->next;
        (*L)->next=p;
    }
}

void CreateList_R(LinkList* L,int n)
{
    LinkList r,p;
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
    r=*L;
    for(int i=0;i<n;i++)
    {
        p=(LinkList)malloc(sizeof(Node));
        scanf("%d",&p->data);
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

void PrintList(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    LinkList L;
    InitList(&L);
    ListInsert(&L,1,10);
    ListInsert(&L,2,20);
    ListInsert(&L,3,30);
    PrintList(L);

    ElemType e;
    ListDelete(&L,2,&e);
    PrintList(L);

    printf("Length:%d\n",ListLength(L));
    DestroyList(&L);

    return 0;
}