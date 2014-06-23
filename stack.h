/**
 *  @file stack.h
 *  @brief - Definicije funkcija za rad sa stekom.
 */
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAXSTACK 2000

typedef struct {
    int contents[MAXSTACK];
    int top;
} stack;

int stackEmpty(stack * myStack);

void stackPush(stack * myStack, int pushMe);

int stackPop(stack * myStack);
#endif // STACK_H_INCLUDED
