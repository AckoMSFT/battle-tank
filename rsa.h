#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

/**
 *  @brief - ( a ^ b ) % c
 *  @param a, b, c
 */
int pow ( int a, int b, int c );

bool check ( int difficulty );

#endif // RSA_H_INCLUDED
