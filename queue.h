#ifndef QUEUЕ_H_INCLUDED
#define QUEUЕ_H_INCLUDED

#define QUEUEMAX 2000

typedef struct {
    int contents[QUEUEMAX];
    int front,end;
} queue;


int queueEmpty(queue * myQueue);

void queuePush(queue * myQueue, int pushMe);

int queuePop(queue * myQueue);

#endif // QUEUЕ_H_INCLUDED
