#include "global.h"

int queueEmpty(queue * myQueue){
    if (myQueue->front == myQueue->end) return 1;
    else return 0;
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
