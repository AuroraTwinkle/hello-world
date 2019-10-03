//
// Created by Administrator on 2019/10/1.
//

#ifndef DATASTRUCTURE_SECTION2_H
#define DATASTRUCTURE_SECTION2_H

#include "utilities.h"

int reverse(sqList *list);//P18 二.2
int deleteX(sqList *list, int element);//P18 二.3
int deleteX1(sqList *list, int element);//P18 二.3
int deleteBtw(sqList *list, int s, int t);//P18 二.5
int deleteBtw1(sqList *list, int s, int t);//P18 二.4

int reverse(sqList *list) {
    if (list == NULL || list->length < 1) { return -1; }
    int tmp = 0;
    int *pHead = list->data;
    int *pTail = pHead + list->length - 1;
    int len = list->length;
    for (int i = 0; i < len / 2; i++) {
        tmp = *pHead;
        *pHead = *pTail;
        *pTail = tmp;
        pHead++;
        pTail--;
    }
    return 1;
}

int deleteX(sqList *list, int element) {
    if (list == NULL || list->length < 1) {
        return -1;
    }
    int *pHead = list->data;
    int count = 0;
    int len = list->length;
    for (int i = 0; i < len; i++) {
        if (*pHead == element) {
            count++;
        } else {
            *(pHead - count) = *pHead;
        }
        if (i < len - 1)
            pHead++;
    }
    list->length -= count;
    return 1;
}

int deleteX1(sqList *list, int element) {
    if (list == NULL || list->length < 1) {
        return -1;
    }
    int *pHead = list->data;
    int *ptr = list->data;
    int count = 0;
    int len = list->length;
    for (int i = 0; i < len; i++) {
        if (*ptr != element) {
            *pHead = *ptr;
            count++;
            if (i < len - 1)
                pHead++;
        }
        if (i < len - 1)
            ptr++;
    }
    list->length = count;
    return 1;
}

int deleteBtw(sqList *list, int s, int t) {
    if (list == NULL || list->length < 1) { return -1; }
    int *pHead = list->data;
    int *ptr = list->data;
    int count = 0;
    int len = list->length;
    for (int i = 0; i < len; i++) {
        if (*ptr < s || *ptr > t) {
            *pHead = *ptr;
            count++;
            if (i < len - 1)
                pHead++;
        }
        if (i < len - 1)
            ptr++;
    }
    list->length = count;
    return 1;
}

int deleteBtw1(sqList *list, int s, int t) {
    if (list == NULL || list->length < 1) { return -1; }
    int *pHead = list->data;
    int *ptr = list->data;
    int *pTail=list->data+list->length-1;
    for (int i = 0; i < list->length; i++) {
        if (*pHead >= s) { break; }
        if (i < list->length - 1)
            pHead++;
    }
    ptr=pHead;
    while (ptr<=pTail){
        if(*ptr>t){ break;}
        ptr++;
    }
    list->length-=ptr-pHead;
    while (ptr<=pTail){
        *pHead=*ptr;
        pHead++;
        ptr++;
    }

    return 1;
}


#endif //DATASTRUCTURE_SECTION2_H
