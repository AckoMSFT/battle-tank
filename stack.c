/**
 *  @file stack.c
 *  @brief - Implementacije funkcija za rad sa stekom.
 */
 #include "global.h"

bool stackEmpty(stack * myStack){
    if (myStack->top) return false;
    else return true;
}

void stackPush(stack * myStack, int pushMe){
    myStack->contents[myStack->top] = pushMe;
    myStack->top++;
}

int stackPop(stack * myStack){
    myStack->top--;
    return myStack->contents[myStack->top];
}
