/**
 *  @file ai.h
 *  @brief - Definicija funkcija za vestacku inteligenciju.
 */
#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

/**
 *  @brief - Vraca .
 *  @param *x, *y pokazivaci na varijable u koje ce se upisati pozicija
 */
void updateDecisions(Tank *tank,float baseRandom, float mytankRandom, int chaseMeX, int chaseMeY, int aiSpeed, int aiParam1 ,int aiParam2, int dontShoot);

/**
 *  @brief - Funkcija za odredjivanje pozicije novog neprijateljskog tenka.
 *  @param *x, *y pokazivaci na varijable u koje ce se upisati pozicija
 */
int get_decision_easy(Tank *tank);

/**
 *  @brief - Funkcija za odredjivanje pozicije novog neprijateljskog tenka.
 *  @param *x, *y pokazivaci na varijable u koje ce se upisati pozicija
 */
int get_decision_medium(Tank *tank);

/**
 *  @brief - Funkcija za odredjivanje pozicije novog neprijateljskog tenka.
 *  @param *x, *y pokazivaci na varijable u koje ce se upisati pozicija
 */
int get_decision_hard(Tank *tank);

/**
 *  @brief - Funkcija za odredjivanje pozicije novog neprijateljskog tenka.
 *  @param *x, *y pokazivaci na varijable u koje ce se upisati pozicija
 */
int get_decision_demo();
#endif AI_H_INCLUDED
