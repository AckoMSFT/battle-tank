#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

void go_up( Tank *tank )
{
    int up = tank->x - 1;
    int x = tank->x, y = tank->y;
    if ( ( map[ up ][ y ] == EMPTY ) && ( map[ up ][ y + 1 ] == EMPTY ) && ( map[ up ][ y + 2 ] == EMPTY ) )
        if ( tank->dir == UP )
        {
            tank->x = up;
         }
        else
        {
            tank->dir = UP;
            tank->x = up;
        }
}
void go_down( Tank *tank )
{
    int down = tank->x + 3;
    int x = tank->x, y = tank->y;
    if ( ( map[ down ][ y ] == EMPTY ) && ( map[ down ][ y + 1 ] == EMPTY ) && ( map[ down ][ y + 2 ] == EMPTY ) )
        if ( tank->dir == DOWN )
        {
            tank->x = down - 2;
         }
        else
        {
            tank->dir = DOWN;
            tank->x = down - 2;
        }
}
void go_left( Tank *tank )
{
    int left = tank->y - 1;
    int x = tank->x, y = tank->y;
    if ( ( map[ x ][ left ] == EMPTY ) && ( map[ x + 1 ][ left ] == EMPTY ) && ( map[ x + 2 ][ left ] == EMPTY ) )
        if ( tank->dir == LEFT )
        {
            tank->y = left;
        }
        else
        {
            tank->dir = LEFT;
            tank->y = left;
        }
}
void go_right( Tank *tank )
{
    int right = tank->y + 3;
    int x = tank->x, y = tank->y;
    if ( ( map[ x ][ right ] == EMPTY ) && ( map[ x + 1 ][ right ] == EMPTY ) && ( map[ x + 2 ][ right ] == EMPTY ) )
        if ( tank->dir == RIGHT )
        {
            tank->y = right - 2;
        }
        else
        {
            tank->dir = RIGHT;
            tank->y = right - 2;
        }
}
//void shoot( Tank tank )
//{
//    int i;
//    for ( i = 0; i < 20; i++)
//        if ( !bullets[ i ] )
//        {
//            bullets[ i ] = malloc( sizeof( Bullet ) );
//            bullets[ i ]->x = tank->x;
//            bullets[ i ]->y = tank->y;
//            bullets[ i ]->dir = tank->dir;
//            break;
//        }
//}
//void update_game()
//{

#endif // ENGINE_H_INCLUDED
