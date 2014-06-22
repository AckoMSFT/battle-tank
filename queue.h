#ifndef queue_H
#define queue_H

#define QUEUEMAX 2000

typedef struct {
    int contents[QUEUEMAX];
    int front,end;
} queue;


int queueEmpty(queue * myQueue);

void queuePush(queue * myQueue, int pushMe);

int queuePop(queue * myQueue);


#endif
