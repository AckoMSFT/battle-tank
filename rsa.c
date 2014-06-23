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

void check ( int difficulty )
{
    char c, temp[42];
    int cnt = 0, d;
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
    if ( temp == NULL || rsa == NULL ) clear_high_scores ( difficulty );
    while ( fscanf ( high_scores, "%c", &c ) != EOF )
    {
        int curr = c;
        int encrypt = pow ( curr, RSA_E, RSA_N );
        if ( fscanf ( rsa, "%d", &d ) == EOF )
        {
            fclose ( high_scores );
            fclose ( rsa );
            clear_high_scores ( difficulty );
            return;
        }
        if ( d != encrypt )
        {
            fclose ( high_scores );
            fclose ( rsa );
            clear_high_scores ( difficulty );
            return;
        }
    }
    fclose ( high_scores );
    fclose ( rsa );
    return true;
}

void encrypt ( int difficulty )
{
    char c, temp[42];
    int cnt = 0, d;
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
    strcpy ( temp, "rsa" );
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
    rsa = fopen ( temp, "w" );
    while ( fscanf ( high_scores, "%c", &c ) != EOF )
    {
        int curr = c;
        fprintf ( rsa, "%d\n", pow ( curr, RSA_E, RSA_N ) );
    }
    fclose ( high_scores );
    fclose ( rsa );
}

void decrypt ( int c, int n, int d )
{
    return pow ( c, d, n );
}
