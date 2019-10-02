//
// Created by Administrator on 2019/10/1.
//

#ifndef DATASTRUCTURE_UTILITIES_H
#define DATASTRUCTURE_UTILITIES_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "stack.h"

typedef struct SqList {
    int *data;
    int length;
} sqList;

sqList *getSeqList();

void printArray(int *array, int length);

void printSeqList(sqList *list);

int getArray(int **array);

void sortSeqList(sqList *list);

void sortQuick(int *pHead, int *pTail);

int *getMiddle(int *pHead, int *pTail);

void quickSortByStack(sqList *list);

int getArray(int **array) {
    srand((unsigned) time(NULL));
    int length = rand() % 10 + 10000000;
    if (length <= 0) {
        return -1;
    }
    int *arrayData = (int *) malloc(sizeof(int) * length);
    if (arrayData == NULL) {
        printf("fail to request for memory\n");
        return -1;
    }

    *array = arrayData;

    for (int i = 0; i < length; i++) {

        *arrayData = rand() % 20;
        if (i == length - 1) { break; }
        arrayData++;
    }
    //printArray(array,length);
    return length;
}

sqList *getSeqList() {
    sqList *list = (sqList *) malloc(sizeof(sqList));
    if (list == NULL) {
        printf("fail to request for memory\n");
        return NULL;
    }
    list->data = NULL;
    int len = getArray(&(list->data));
    list->length = len;
    return list;
}

void printSeqList(sqList *list) {
    printArray(list->data, list->length);
}

void printArray(int *array, int length) {
    if (length <= 0) {
        return;
    }
    for (int i = 0; i < length; i++) {
        printf("%d\t", *array);
        array++;
    }
    printf("\n");
}


void sortQuick(int *pHead, int *pTail) {
    if (pHead == NULL || pTail == NULL || pHead >= pTail) { return; }
    int *middle = getMiddle(pHead, pTail);
    sortQuick(pHead, middle - 1);
    sortQuick(middle + 1, pTail);
}

int *getMiddle(int *pHead, int *pTail) {
    if (pHead == NULL || pTail == NULL) { return NULL; }
    int midFlag = *pHead;
    while (pHead < pTail) {
        while (*pTail >= midFlag && pHead < pTail) {
            (pTail)--;
        }
        *pHead = *pTail;
        while (midFlag >= *pHead && pHead < pTail) {
            (pHead)++;
        }
        *pTail = *pHead;
    }
    *pHead = midFlag;
    return pHead;
}

void sortSeqList(sqList *list) {
    if (list == NULL || list->length < 1) { return; }
    int *pHead = list->data;
    int *pTail = pHead + list->length - 1;
    sortQuick(pHead, pTail);
}

void quickSortByStack(sqList *list) {
    if (list == NULL || list->length < 1) { return; }
    stack s;
    if (newStack(&s, sizeof(int **) )!= 1) { return; }
    int *pHead = list->data;
    int *pTail = list->data + list->length - 1;
    if(pushStack(&s,&pTail)!=1){ return;}
    if(pushStack(&s,&pHead)!=1){ return;}
    while (isEmpty(&s)!=1){
        printf("stack length:%d\n",s.length);
        if((popStack(&s,&pHead)!=1)){ return;}
        if((popStack(&s,&pTail)!=1)){ return;}
        int *middle=getMiddle(pHead,pTail);
        if(middle-1>pHead){
            int *ptr=middle-1;
            if(pushStack(&s,&ptr)!=1){ return;}
            if(pushStack(&s,&pHead)!=1){ return;}
        }
        if(middle+1<pTail){
            int *ptr=middle+1;
            if(pushStack(&s,&pTail)!=1){ return;}
            if(pushStack(&s,&ptr)!=1){ return;}
        }
    }
}

#endif //DATASTRUCTURE_UTILITIES_H
