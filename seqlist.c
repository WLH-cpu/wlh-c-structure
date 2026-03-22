#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType* data;
    int length;
}SqList;

Status InitList(SqList* L)
{
    L->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    if(!L->data) exit(OVERFLOW);
    L->length=0;
    return OK;
}

void DistroyList(SqList* L)
{
    if(L->data) free(L->data);
}

void ClearList(SqList* L)
{
    L->length=0;
}

int GetLength(SqList L)
{
    return L.length;
}

Status isEmpty(SqList L)
{
    if(L.length) return FALSE;
    else return TRUE;
}

Status GetElem(SqList L,int i,ElemType* e)
{
    if(i<1||i>L.length) return ERROR;
    *e=L.data[i-1];
    return OK;
}

int LocateElem(SqList L,ElemType e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]==e) return i+1;
    }
    return 0;
}

Status ListInsert(SqList* L,int i,ElemType e)
{
    if(i<1||i>L->length+1||L->length==MAXSIZE) return ERROR;
    for(int j=L->length-1;j>=i-1;j--)
    {
        L->data[j+1]=L->data[j];
    }
    L->data[i-1]=e;
    L->length++;
    return OK;
}

Status ListDelete(SqList* L,int i,ElemType* e)
{
    if(i<1||i>L->length||L->length==0) return ERROR;
    *e=L->data[i-1];
    for(int j=i;j<L->length;j++)
    {
        L->data[j-1]=L->data[j];
    }
    L->length--;
    return OK;
}

void ListTraverse(SqList L)
{
    for(int i=0;i<L.length;i++)
    {
        printf("%d ",L.data[i]);
    }
}

int main()
{
    SqList L;
    InitList(&L);
    //插入测试
    ListInsert(&L,1,10);
    ListInsert(&L,2,20);
    ListInsert(&L,3,30);
    ListInsert(&L,4,40);
    ListInsert(&L,5,50);

    printf("插入后的顺序表：");
    ListTraverse(L);
    printf("\n");
    //获取长度测试
    printf("当前长度：%d\n",GetLength(L));
    //按位查找测试
    ElemType e;
    GetElem(L,3,&e);
    printf("第三个元素：%d\n",e);
    //按值查找
    int pos=LocateElem(L,40);
    printf("元素40的位置：%d\n",pos);
    //删除测试
    ListDelete(&L,2,&e);
    ListTraverse(L);
    printf("\n");
    //是否为空测试
    printf("是否为空：%s\n",isEmpty(L)?"是":"否");
    //清空表
    ClearList(&L);
    printf("清空后长度：%d\n",GetLength(L));
    printf("清空后是否为空：%s\n",isEmpty(L)?"是":"否");
    //释放空间
    DistroyList(&L);

    return 0;
}