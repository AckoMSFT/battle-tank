/**
 *  @file queue.h
 *  @brief - Definicija funkcija i strukture za rad sa neprioritetnim redom.
 */
#ifndef QUEUЕ_H_INCLUDED
#define QUEUЕ_H_INCLUDED

#define QUEUEMAX MAP_SIZE*MAP_SIZE

/**
 *  @brief - Struktura reda.
 */
typedef struct {
    int contents[QUEUEMAX]; /**< sadrzaj reda*/
    int front; /**< pocetak reda*/
    int end; /**< kraj reda*/
} queue;


/**
 *  @brief - Provera da li je red prazan.
 *  @param *myQueue pokazivac na red
 *  @return Funkcija vraca true ako je red prazan, a u suprotnom false.
 */
bool queueEmpty(queue * myQueue);

/**
 *  @brief - Dodavanje na kraj reda.
 *  @param *myQueue pokazivac na red
 *  @param pushMe broj koji se dodaje na kraj reda
 */
void queuePush(queue * myQueue, int pushMe);

/**
 *  @brief - Skidanje sa pocetka reda.
 *  @param *myQueue pokazivac na red
 *  @return Funkcija vraca sadrzaj pocetka reda.
 */
int queuePop(queue * myQueue);

#endif // QUEUЕ_H_INCLUDED
