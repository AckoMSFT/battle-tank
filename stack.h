/**
 *  @file stack.h
 *  @brief - Definicije funkcija za rad sa stekom.
 */
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAXSTACK MAP_SIZE*MAP_SIZE

/**
 *  @brief - Struktura steka.
 */
typedef struct {
    int contents[MAXSTACK]; /**< sadrzaj steka*/
    int top; /**< vrh steka*/
} stack;

/**
 *  @brief - Provera da li je stek prazan.
 *  @param *myStack pokazivac na red
 *  @return Funkcija vraca true ako je stek prazan, a u suprotnom false.
 */
bool stackEmpty(stack * myStack);

/**
 *  @brief - Dodavanje na vrh steka.
 *  @param *myStack pokazivac na stek
 *  @param pushMe broj koji se dodaje na vrh steka
 */
void stackPush(stack * myStack, int pushMe);

/**
 *  @brief - Skidanje sa vrha steka.
 *  @param *myStack pokazivac na stek
 *  @return Funkcija vraca sadrzaj vrha steka.
 */
int stackPop(stack * myStack);

#endif // STACK_H_INCLUDED
