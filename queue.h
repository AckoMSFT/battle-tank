/**
 *  @file queue.h
 *  @brief - Definicija funkcija i strukture za rad sa neprioritetnim redom.
 */
#ifndef QUEUЕ_H_INCLUDED
#define QUEUЕ_H_INCLUDED

#define QUEUEMAX MAP_SIZE*MAP_SIZE

typedef struct {
    int contents[QUEUEMAX];
    int front,end;
} queue;


int queueEmpty(queue * myQueue);

void queuePush(queue * myQueue, int pushMe);

int queuePop(queue * myQueue);

#endif // QUEUЕ_H_INCLUDED
