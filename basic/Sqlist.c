#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 100

typedef struct{
    int *elme;
    int length;
}List,*ListPtr;

void Init_Sqlist(ListPtr L);
void List_Destory(ListPtr L);
void List_Clear(ListPtr L);
bool List_Empty(ListPtr L);
void List_Prior(ListPtr L,int pos);
void List_Next(ListPtr L,int pos);
void List_Display(ListPtr L);
void List_Delete(ListPtr L,int pos);
void List_Insert(ListPtr L,int pos,int elme);
void List_Search(ListPtr L,int pos);//按位置查找
void List_Search1(ListPtr L,int elme);//按值查找

int main(void)
{
    ListPtr list;
    List L;
    list = &L;
    Init_Sqlist(list);
    for(int i=0;i<MAXSIZE-5;i++)
    {
        list->elme[i] = i;
        list->length++;
    }
    List_Insert(list,5,55);
    List_Delete(list,5);
    List_Search(list,10);
    List_Search1(list,25);
    List_Display(list);

    return 0;
}

void Init_Sqlist(ListPtr L)
{
    L->elme = (int *)malloc((MAXSIZE+1) * sizeof(int));
    if(L->elme)
    {
        L->length = 0;
    }
}

void List_Destory(ListPtr L)
{
    if (L->elme)
    {
        free(L->elme);
    }
    L->length = 0;
}

void List_Clear(ListPtr L)
{
    L->length = 0;
}

bool List_Empty(ListPtr L)
{
    return L->length == 0;
}

void List_Prior(ListPtr L,int pos)
{
    int *elme;
    int len = L->length;
    if(2<=pos && pos<=len)
    {
        *elme = L->elme[pos-1];
        printf("%d\t",*elme);
    }
}

void List_Next(ListPtr L,int pos)
{
    int *elme;
    int len = L->length;
    if(2<=pos && pos<=len)
    {
        *elme = L->elme[pos+1];
        printf("%d\t",*elme);
    }
}

void List_Display(ListPtr L)
{
    int len = L->length;
    for(int i=0;i<len;i++)
    {
        printf("%d\t",L->elme[i]);
    }
}

void List_Search(ListPtr L,int pos)
{
    int len = L->length;
    if(1<=pos && pos<=len)
    {
        printf("%d\t",L->elme[pos]);
    }
}

void List_Search1(ListPtr L,int elme)
{
    int len = L->length;
    for(int i=1;i<=len;i++)
    {
        if(L->elme[i]==elme)
        {
            printf("%d\t",i);
        }
    }
}

void List_Insert(ListPtr L,int pos,int elme)
{
    int len = L->length;
    if(len>MAXSIZE)
    {
        return ;
    }
    else if(1<=pos && pos <=len+1)
    {
        for(int i=len;i>=pos;i--)
        {
            L->elme[i+1] = L->elme[i];
        }
        L->elme[pos] = elme;
        L->length++;
    }
}

void List_Delete(ListPtr L,int pos)
{
    int len = L->length;
    if(1<=pos && pos<=len)
    {
        for(int i=pos;i<len;i++)
        {
            L->elme[i] = L->elme[i+1];
        }
        L->length--;
    }

}
