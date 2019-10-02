#include <stdio.h>
#include <stdlib.h>

struct ListNode {
      int val;
      struct ListNode *next;
 };

 /*struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
 {
     struct ListNode *l3;
     struct ListNode *p=NULL;
     l3 = (struct ListNode *)malloc(sizeof(struct ListNode));
     l3 -> next = NULL;
     int carry = 0;//进位
     while(l1 != NULL || l2 != NULL || carry != 0)
     {
         if(p == NULL)
         {
             p = l3;
         }
         else{
             p->next=(struct ListNode *)malloc(sizeof(struct ListNode));
             p->next->val=0;
             p=p->next;
         }
         int a = l1 != NULL ? l1 -> val : 0;
         int b = l2 != NULL ? l2 -> val : 0;
         int sum = (a+b+carry)%10;
         carry = (a+b+carry)/10;
         p -> val = sum;
         p -> next = NULL;
         l1 = l1 == NULL ? NULL : l1 -> next;
         l2 = l2 == NULL ? NULL : l2 -> next;
     }
     return l3=l3->next;
 }*/


 struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
 {
     struct ListNode *l3;
     struct ListNode *p=NULL;
     l3 = (struct ListNode *)malloc(sizeof(struct ListNode));
     l3 -> next = NULL;
     int carry = 0;//进位
     int val = 0;
     while(l1 != NULL || l2 != NULL || carry != 0)
     {
         if(p == NULL)
         {
             p=l3;
         }
         else{
            p->next=(struct ListNode *)malloc(sizeof(struct ListNode));
            p->next->val=0;
            p=p->next;             
         }
         if(l1 != NULL || carry != 0)
         {
             val += (l1==NULL ? 0 : l1 -> val) + carry;
             l1 = l1==NULL ? NULL : l1 -> next;
         }
         carry = 0;
         if(l2 != NULL)
         {
             val += (l2->val) + carry;
             l2 = l2 -> next;
         }
         if(val >= 10)
         {
             val = val - 10;
             carry = 1;
         }
         p->val = val;
         p->next = NULL;
         
         val = 0;
     }
     return l3;
 }
