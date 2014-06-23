/**
 *  @file ai.h
 *  @brief - Definicija funkcija za vestacku inteligenciju.
 */
#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

/**
 *  @brief - Azurira vestacku inteligenciju tenka *tank.
 *  @param *tank tenk cija se vestacka inteligencija azurira
 *  @param baseRandom verovatnoca da se tenk krece ka bazi
 *  @param chaseRandom, chaseMeX, chaseMeY verovatnoca da se tenk krece ka objektu na koordinatama chaseMeX i chaseMeY
 *  @param aiSpeed koliko odluka unapred ova funkcija upisuje u niz odluka tenka
 *  @param aiParam1 odredjuje koliko ima istih odluka za redom ukoliko je odlucivanje slucajno
 *  @param aiParam2 odredjuje odnos odluka pucanja i odluka kretanja ukoliko je odlucivanje slucajno
 *  @param dontShoot predstavlja 1 ukoliko tenk treba samo da ide ka meti, 0 ako treba da je puca
 */
void updateDecisions(Tank *tank,float baseRandom, float chaseRandom,int chaseMeX, int chaseMeY, int aiSpeed, int aiParam1, int aiParam2, bool dontShoot);

/**
 *  @brief - Poziva funkciju za azuriranje vestacke inteligencije za neprijateljski tenk za najmanju tezinu igrice
 *  @param *tank tenk za koji se azurira vestacka inteligencija
 *  @return Funkcija vraca odluku za zadatu tezinu igre i zadati tenk.
 */
int get_decision_easy(Tank *tank);

/**
 *  @brief - Poziva funkciju za azuriranje vestacke inteligencije za neprijateljski tenk za srednju tezinu igrice
 *  @param *tank tenk za koji se azurira vestacka inteligencija
 *  @return Funkcija vraca odluku za zadatu tezinu igre i zadati tenk.
 */
int get_decision_medium(Tank *tank);

/**
 *  @brief - Poziva funkciju za azuriranje vestacke inteligencije za neprijateljski tenk za najvecu tezinu igrice
 *  @param *tank tenk za koji se azurira vestacka inteligencija
 *  @return Funkcija vraca odluku za zadatu tezinu igre i zadati tenk.
 */
int get_decision_hard(Tank *tank);

/**
 *  @brief - Poziva funkciju za azuriranje vestacke inteligencije igraca u demo modu
 *  @return Funkcija vraca odluku za igraca u demo modu.
 */
int get_decision_demo();

#endif AI_H_INCLUDED
