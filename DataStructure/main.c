#include <stdio.h>
#include "utilities.h"
#include "section2.h"
#include "stack.h"
int main() {
//    stack s;
//    newStack(&s, sizeof(int **));
//    int num=12;
//    int *tmp=&num;
//    pushStack(&s, &tmp);
//    popStack(&s,&tmp);
    sqList *list = getSeqList();
    printSeqList(list);
    //reverse(list);
    //deleteX(list,10);
    //deleteX1(list,10);
    //deleteBtw(list,4,10);
    quickSortByStack(list);
    printSeqList(list);
    deleteBtw1(list,0,10);
    //sortSeqList(list);
    printSeqList(list);
    if (list->data != NULL) {
        free(list->data);
        list->data = NULL;
    }
    free(list);
    list = NULL;
    return 0;
}