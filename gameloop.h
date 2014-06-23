/**
 *  @file gameloop.h
 *  @brief - Definicija funkcija za tok igrice.
 */
#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED
#define DEBUG 0

/**
 *  @brief - Funkcija za odredjivanje pozicije novog neprijateljskog tenka.
 *  @param *x, *y pokazivaci na varijable u koje ce se upisati pozicija
 */
void find_space_tank(int *x, int *y);

/**
 *  @brief - Azurira mapu zauzetih polja.
 *  @param usePowerUp predstavlja 1 ako treba da se azurira pojacanje, 0 u suprotnom
*/
void update_mapUsed(bool usePowerUp);

/**
 *  @brief - Azurira mapu zauzetih polja.
 *  @param usePowerUp predstavlja 1 ako treba da se azurira pojacanje, 0 u suprotnom
*/
//start the gameloop
void startGame();


int startLevel(int level);

#endif // GAMELOOP_H_INCLUDED
