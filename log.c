struct Tank
{
    int dir, x, y;
};
void go_up( Tank tank )
{
    int up = tank.x - 1;
    if ( ( map[ up ][ y ] == EMPTY ) && ( map[ up ][ y + 1 ] == EMPTY ) && ( map[ up ][ y + 2 ] == EMPTY ) )
        if ( tank.dir == UP )
        {
            erase_tank( tank.x, tank.y );
            tank.x = up;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = UP;
            print_tank( tank.dir, tank.x, tank.y );
            tank.x = up;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void go_down( Tank tank )
{
    int down = tank.x + 3;
    if ( ( map[ down ][ y ] == EMPTY ) && ( map[ down ][ y + 1 ] == EMPTY ) && ( map[ down ][ y + 2 ] == EMPTY ) )
        if ( tank.dir == DOWN )
        {
            erase_tank( tank.x, tank.y );
            tank.x = down;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = DOWN;
            print_tank( tank.dir, tank.x, tank.y );
            tank.x = down;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void go_left( Tank tank )
{
    int left = tank.y - 1;
    if ( ( map[ x ][ left ] == EMPTY ) && ( map[ x + 1 ][ left ] == EMPTY ) && ( map[ x + 2 ][ left ] == EMPTY ) )
        if ( tank.dir == LEFT )
        {
            erase_tank( tank.x, tank.y );
            tank.y = left;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = LEFT;
            print_tank( tank.dir, tank.x, tank.y );
            tank.y = left;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void go_right( Tank tank )
{
    int right = tank.y + 3;
    if ( ( map[ x ][ right ] == EMPTY ) && ( map[ x + 1 ][ right ] == EMPTY ) && ( map[ x + 2 ][ right ] == EMPTY ) )
        if ( tank.dir == RIGHT )
        {
            erase_tank( tank.x, tank.y );
            tank.y = right;
            print_tank( tank.x, tank.y );
        }
        else
        {
            tank.dir = RIGHT;
            print_tank( tank.dir, tank.x, tank.y );
            tank.y = left;
            print_tank( tank.dir, tank.x, tank.y );
        }
}

int main()
{

    while ( 1 )
    {
        c = getch();
        switch( c )
        {
            get_me_out_of_here = 0;
            case KEY_UP: go_up( tank ); break;
            case KEY_DOWN: go_down( tank ); break;
            case KEY_RIGHT: go_right( tank ); break;
            case KEY_LEFT: go_left( tank ); break;
            case
        }


