/**
 *  @file highscores.h
 *  @brief - Definicije funkcija za rad sa listom najboljih rezultata.
 */
#ifndef HIGHSCORES_H_INCLUDED
#define HIGHSCORES_H_INCLUDED

/**
 *  @brief - Upisivanje igraca u odgovarajucu listu najboljih rezultata.
 *  @param name ime igraca
 *  @param score rezultat
 *  @param difficulty tezina
 */
void update_high_scores (char name[], int score, int difficulty);

#endif // HIGHSCORES_H_INCLUDED


