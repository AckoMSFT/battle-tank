#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stackEmpty(stack * myStack){
    if (myStack->top) return 0;
    else return 1;
}

void stackPush(stack * myStack, int pushMe){
    myStack->contents[myStack->top] = pushMe;
    myStack->top++;
}

int stackPop(stack * myStack){
    myStack->top--;
    return myStack->contents[myStack->top];
}
