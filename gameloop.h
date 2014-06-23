/**
 *  @file gameloop.h
 *  @brief - Definicija funkcija za tok igrice.
 */
#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED

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
 *  @brief - Inicijalizuje pocetak igrice, i pokrece startLevel funkciju redom po nivoima.
*/
void startGame();

/**
 *  @brief - Inicijalizuje odgovarajuci nivo i pokrece petlju igrice
 *  @param level nivo koji se pokrece
 *  @return Funkcija vraca true ako je nivo uspesno predjen, a u suprotnom false.
*/
bool startLevel(int level);

#endif // GAMELOOP_H_INCLUDED
