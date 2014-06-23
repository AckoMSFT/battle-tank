#include "global.h"

int pow ( int a, int b, int c )
{
    int ret = 1;
    a %= c;
    while ( b )
    {
        if ( b % 2 == 1 ) ret = ( ret * a ) % c;
        a = ( a * a ) % c;
        b = b / 2;
    }
    return ret;
}

bool check ( int difficulty )
{
    char c, temp[42];
    FILE * high_scores, * rsa;
    strcpy ( temp, "high_scores" );
    switch ( difficulty )
    {
    case 0:
        strcat ( temp, "_easy.txt" );
        break;
    case 1:
        strcat ( temp, "_medium.txt" );
        break;
    case 2:
        strcat ( temp, "_hard.txt" );
        break;
    }
    high_scores = fopen ( temp, "r" );
    strcpy ( temp, "rsa");
    switch ( difficulty )
    {
    case 0:
        strcat ( temp, "_easy.txt" );
        break;
    case 1:
        strcat ( temp, "_medium.txt" );
        break;
    case 2:
        strcat ( temp, "_hard.txt" );
        break;
    }
    rsa = fopen ( temp, "r" );
    while ( fscanf ( high_scores, "%c", &c ) != EOF )
    {
        int curr = c;
        int encrypt = pow ( curr, RSA_E, RSA_N );
        printf ( "%c %d %c\n", c, encrypt,(char)decrypt(encrypt,RSA_N,RSA_D));
    }
    fclose ( high_scores );
    fclose ( rsa );
}

void decrypt ( int c, int n, int d )
{
    return pow ( c, d, n );
}
