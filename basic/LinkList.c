#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct node{
    int data;
    struct node *next;
}ListNode,*ListNodePtr;

ListNodePtr head,Pre_ptr;

void InitList();
void BuildList();
void DisplayList();
void SearchList(int data);//按值查找
void SearchList1(int pos);//按位置查找
void ReverseList();//头插法逆置
void ReverseList1();
void FreeList(ListNodePtr head);
void InsertList(int pos,int data);
void DeleteList(int pos);
void setPositionList(int pos,ListNodePtr *ptr);

int main(void)
{
    InitList();
    BuildList();
    DisplayList();
    //ReverseList1();
    InsertList(5,468);
    DeleteList(5);
    DisplayList();
    SearchList(100);
    SearchList1(5);
    FreeList(head);
    return 0;
}

void InitList()
{
    head = (ListNodePtr)malloc(sizeof(ListNode));
    head->next=NULL;
    if(head==NULL)
    {
        printf("Fail to request for room!");
    }
    Pre_ptr = (ListNodePtr)malloc(sizeof(ListNode));
    Pre_ptr->next=NULL;
    if(Pre_ptr==NULL)
    {
        printf("Fail to request for room!");
    }
}

void BuildList()
{
    srand( (unsigned)time( NULL ) );
    for(int i=0;i<10;i++)
    {
        ListNodePtr p;
        p = (ListNodePtr)malloc(sizeof(ListNode));
        //p -> data = rand()%100+1;
        p -> data = i;
        p -> next = NULL;
        if(head -> next == NULL)
        {
            head -> next = p;
            Pre_ptr = p;
        }
        Pre_ptr -> next = p;
        Pre_ptr = p;
    }
}

void DisplayList()
{
    ListNodePtr p;
    p = head -> next;
    while(p)
    {
        printf("%d\t",p->data);
        p = p -> next;
    }
}

void ReverseList()
{
    ListNodePtr p,q;
    p = head -> next;
    head -> next = NULL;
    while(p)
    {
        q = p;
        p = p -> next;
        q -> next = head -> next;
        head -> next = q;
    }
}

void ReverseList1()
{
    ListNodePtr p,q,t;
    p = head -> next;
    q = t = NULL;
    while(p)
    {
        q = p -> next;
        p -> next = t;
        t = p;
        p = q;
    }
    head -> next = t;
}

void FreeList(ListNodePtr head)
{
    while(head)
    {
        ListNodePtr temp = head -> next;
        free(head);
        head = temp;
    }
}

void SearchList(int data)
{
    ListNodePtr p;
    p = head -> next;
    int search_result = 0;
    int turn = 1;
    while(p && search_result == 0)
    {
        turn++;
        if(p->data == data)
        {
            printf("%d",turn);
            search_result = 1;
        }
        p = p -> next;
    }
    if(search_result == 0)
    {
        printf("Not found this value!");
    }
}

void SearchList1(int pos)
{
    ListNodePtr q;
    setPositionList(pos,&q);
    printf("%d",q->data);

}

void setPositionList(int pos,ListNodePtr *ptr)
{
    ListNodePtr p = head -> next;
    int i = 1;
    while(p && i<pos)
    {
        i++;
        p = p -> next;
    }
    if(p && i == pos)
    {
        *ptr = p;
    }
    else
    {
        printf("Not found this node!");
    }
}

void InsertList(int pos,int data)
{
    ListNodePtr p,q;
    setPositionList(pos-1,&p);
    q = (ListNodePtr)malloc(sizeof(ListNode));
    q -> data = data;
    q -> next = p -> next;
    p -> next = q;
}

void DeleteList(int pos)
{
    ListNodePtr p,q;
    setPositionList(pos-1,&p);
    p -> next = q -> next;
    free(q);

}
