#ifndef stack_H
#define stack_H

#define MAXSTACK 2000

typedef struct {
    int contents[MAXSTACK];
    int top;
} stack;

int stackEmpty(stack * myStack);

void stackPush(stack * myStack, int pushMe);

int stackPop(stack * myStack);

#endif
