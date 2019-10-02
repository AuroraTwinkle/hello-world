#include <stdio.h>
#include <stdlib.h>

struct ListNode {
      int val;
      struct ListNode *next;
};
 
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) 
{
	if (head->next == NULL) return NULL;
    struct ListNode* p1 = head;
    struct ListNode* p2 = head;
    while(p2->next != NULL && n--) p2 = p2->next;
    while(p2->next != NULL) 
    {
    	p1 = p1->next;
    	p2 = p2->next;
    }
    if (n > 0) 
    {
    	*p1 = *(p1->next);
    } 
    else 
    {
    	p1->next = p1->next->next;
    }
    return head;
}