#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

#define INIT_CAPACITY 10

typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType* data;
    int length;
    int capacity;
}SqList;

static Status ExpandCapacity(SqList* L)
{
    int newCapacity=L->capacity*2;
    ElemType* newData=(ElemType*)realloc(L->data,sizeof(ElemType)*newCapacity);
    if(!newData) exit(OVERFLOW);
    L->data=newData;
    L->capacity=newCapacity;
    return OK;
}

Status InitList(SqList* L)
{
    L->data=(ElemType*)malloc(sizeof(ElemType)*INIT_CAPACITY);
    if(!L->data) exit(OVERFLOW);
    L->length=0;
    L->capacity=INIT_CAPACITY;
    return OK;
}

void DestroyList(SqList* L)
{
    if(L->data)
    {
        free(L->data);
        L->data=NULL;
        L->length=0;
        L->capacity=0;
    }
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
    return L.length==0?TRUE:FALSE;
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
    if(L.data[i]==e) return i+1;
    return 0;
}

Status ListInsert(SqList* L,int i,ElemType e)
{
    if(i<1||i>L->length+1) return ERROR;
    if(L->length==L->capacity) ExpandCapacity(L);
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

void PrintList(SqList L)
{
    for(int i=0;i<L.length;i++)
    {
        printf("%d ",L.data[i]);
    }
    printf("\n");
}

Status ListPushBack(SqList* L,ElemType e)
{
    if(L->length==L->capacity) ExpandCapacity(L);
    L->data[L->length++]=e;
    return OK;
}

Status ListPopBack(SqList* L)
{
    if(L->length==0) return ERROR;
    L->length--;
    return OK;
}

int main()
{
    SqList L;
    ElemType del_val;

    // 初始化
    InitList(&L);
    printf("初始化成功\n");
    printf("是否为空：%s\n\n", isEmpty(L) ? "是" : "否");

    // 尾插
    ListPushBack(&L, 10);
    ListPushBack(&L, 20);
    ListPushBack(&L, 30);
    ListPushBack(&L, 40);
    printf("尾插 10 20 30 40 后：");
    PrintList(L);
    printf("长度：%d\n\n", GetLength(L));

    // 任意位置插入
    ListInsert(&L, 2, 15);
    printf("在第 2 位插入 15 后：");
    PrintList(L);
    printf("长度：%d\n\n", GetLength(L));

    // 查找元素
    int pos = LocateElem(L, 30);
    printf("元素 30 的位置是：%d\n\n", pos);

    // 删除指定位置
    ListDelete(&L, 3, &del_val);
    printf("删除第 3 位元素 %d 后：", del_val);
    PrintList(L);
    printf("长度：%d\n\n", GetLength(L));

    // 尾删
    ListPopBack(&L);
    printf("尾删后：");
    PrintList(L);
    printf("长度：%d\n\n", GetLength(L));

    // 清空
    ClearList(&L);
    printf("清空后是否为空：%s\n\n", isEmpty(L) ? "是" : "否");

    // 销毁
    DestroyList(&L);
    printf("销毁完成\n");

    return 0;
}