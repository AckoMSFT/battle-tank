/**
 *  @file rsa.h
 *  @brief - Definicije funkcija za enkripciju i dekripciju.
 */
#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

/**
 *  @brief - ( a ^ b ) % c
 *  @param a, b, c
 */
int pow ( int a, int b, int c );

/**
 *  @brief - Proverava da li je lista najboljih skorova za odgovarajucu tezinu koruptovana.
 *  @param difficulty tezina
 */
void check ( int difficulty );

/**
 *  @brief - Enkriptuje listu najboljih rezultata za datu tezinu.
 *  @param difficulty tezina
 */
void encrypt ( int difficulty )

/**
 *  @brief - Dekriptuje broj c sa privatnim kljucem (n, d).
 */
void decrypt ( int c, int n, int d );

#endif // RSA_H_INCLUDED
