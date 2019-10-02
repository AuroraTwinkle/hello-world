//
// Created by Administrator on 2019/10/2.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Stack {
    void *element;
    int elemSize;
    int topLength;
    int length;
} stack;

int newStack(stack *stack, int elemSize);

int pushStack(stack *s, void *elemAddr);

int popStack(stack *s, void *elemAddr);

int isEmpty(stack*s);

int growStack(stack *s);

int newStack(stack *stack, int elemSize) {
    stack->elemSize = elemSize;
    stack->length = 4;
    stack->topLength = 0;
    stack->element = (void *) malloc(stack->elemSize * stack->elemSize);
    if (stack->element == NULL) { return -1; }
    return 1;
}

int pushStack(stack *s, void *elemAddr) {
    if (s == NULL) { return -1; }
    if (s->length == s->topLength) {
        if (!growStack(s)) { return -1; }
    }
    void *target = (char *) s->element + (s->elemSize) * (s->topLength);
    memcpy(target, elemAddr, s->elemSize);
    s->topLength++;
    return 1;
}

int growStack(stack *s) {
    if (s == NULL) { return -1; }
    s->length *= 2;
    s->element = realloc(s->element, s->length * s->elemSize);
    if (s->element == NULL) { return -1; }
    return 1;
}

int popStack(stack *s, void *elemAddr) {
    if (s == NULL || s->topLength <= 0) { return -1; }
    void *target = (char *) s->element + (s->topLength - 1) * (s->elemSize);
    memcpy(elemAddr, target, s->elemSize);
    s->topLength -= 1;
    return 1;
}

int isEmpty(stack *s) {
    if(s==NULL||s->topLength<=0){
        return 1;
    }
    return -1;
}

#endif //DATASTRUCTURE_STACK_H
