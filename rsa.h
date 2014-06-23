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

#endif // RSA_H_INCLUDED
