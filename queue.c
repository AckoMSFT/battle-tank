/**
 *  @file gameloop.c
 *  @brief - Implementacije funkcija za rad sa neprioritetnim redom.
 */
#include "global.h"

bool queueEmpty(queue * myQueue){
    if (myQueue->front == myQueue->end) return true;
    else return false;
}

void queuePush(queue * myQueue, int pushMe){
    myQueue->contents[myQueue->end] = pushMe;
    myQueue->end++;
	if (myQueue->end == QUEUEMAX) myQueue->end = 0;
}

int queuePop(queue * myQueue){
    if (myQueue->front == QUEUEMAX) myQueue->front = 0;
    return myQueue->contents[myQueue->front++];
}
