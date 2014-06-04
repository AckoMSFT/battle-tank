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
void shoot( Tank *tank ) // Spawns new bullet after shoot command
{
    int i, x, y;
    switch( tank->dir ){
    case ( UP ):
        x = tank->x - 1;
        y = tank->y + 1;
        break;
    case ( RIGHT ):
        x = tank->x + 1;
        y = tank->y + 3;
        break;
    case ( LEFT ):
        x = tank->x + 1;
        y = tank->y - 1;
        break;
    case ( DOWN ):
        x = tank->x + 3;
        y = tank->y + 1;
        break;
    }
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( !bullets[ i ].val )
        {
            bullets[ i ].val = 1;
            bullets[ i ].x = x;
            bullets[ i ].y = y;
            bullets[ i ].dir = tank->dir;
            bullets[ i ].state = 0;
            break;
        }
}

void update_bullets() // Updating bullets states and moving them
{
    int i;
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( bullets[ i ].val )
        {
            bullets[ i ].state++;
            if ( bullets[ i ].state == 3 )
            {
                switch ( bullets[ i ].dir )
                {
                    case ( UP ):
                        bullets[ i ].x--;
                        break;
                    case ( DOWN ):
                        bullets[ i ].x++;
                        break;
                    case ( LEFT )
                        bullets[ i ].y--;
                        break;
                    case ( RIGHT )
                        bullets[ i ].y++;
                        break;
                }
                bullets[ i ].state = 0;
            }
        }
}

void collision() // Check for collisions of tanks and bullets, respectively bullets and bullets
{
    int i, j;
    for ( i = 0; i < MAXSPRITES; i++ )
        for ( j = 0; j < MAXSPRITES; j++ )
        if ( ( tank[ i ].x == bullets[ j ].x ) && ( tank[ i ].y == bullets[ i ].y ) )
        {
            bullets[ i ].val = 0;
            tank[ i ].val = 0;
        }
    for ( i = 0; i < MAXSPRITES; i++ )
        for ( j = 0; j < MAXSPRITES; j++ )
        if ( ( i != j ) && ( bullets[ i ].x == bullets[ j ].x ) && ( bullets[ i ].y == bullets[ j ].y ) )
        {
            bullets[ i ].val = 0;
            bullets[ j ].val = 0;
        }
}

void spawn_tank( int x, int y, int dir )
{
    int i;
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( !tank[ i ].val )
        {
            tank[ i ].val = 1;
            tank[ i ].dir = dir;
            tank[ i ].x = x;
            tank[ i ].y = y;
            break;
        }
}
#endif // ENGINE_H_INCLUDED
