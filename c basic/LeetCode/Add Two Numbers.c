#include <stdio.h>
#include <stdlib.h>

struct ListNode {
      int val;
      struct ListNode *next;
 };
 
 struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
 {
     struct ListNode *l3;
     struct ListNode *q;
     l3 = (struct ListNode *)malloc(sizeof(struct ListNode));
     l3 -> next = NULL;
     int carry = 0;//进位
     int val = 0;
     while(l1 != NULL || l2 != NULL)
     {
         if(l1 != NULL)
         {
             val = (l1->val) + carry;
             l1 = l1 -> next;
         }
         if(l2 != NULL)
         {
             val = (l2->val) + carry;
             l2 = l2 -> next;
         }
         carry = 0;
         struct ListNode *p = (struct ListNode *)malloc(sizeof(struct ListNode));
         if(val >= 10)
         {
             val = val - 10;
             carry = 1;
         }
         p->val = val;
         p->next = NULL;
         if(l3->next == NULL)
         {
             l3->next = p;
             q = p;
         }
         q -> next = p;
         q = p;
         val = 0;
     }
     return l3;
 }