#include "global.h"

void init_curses ( void )
{
    initscr ( );
    cbreak ( );
    noecho ( );
    keypad ( stdscr, TRUE );
	curs_set ( 0 );
    init_colors ( );
}

void init_colors ( void )
{
    start_color ( );
    init_pair ( 1, COLOR_WHITE , COLOR_BLUE );
    init_pair ( 2, COLOR_BLACK, COLOR_RED );
    init_pair ( 3, COLOR_BLACK, COLOR_WHITE );
    init_pair ( 4, COLOR_BLACK, COLOR_GREEN );
    init_pair ( 5, COLOR_YELLOW, COLOR_RED );
    init_pair ( 6, COLOR_BLACK, COLOR_MAGENTA );
    init_pair ( 7, COLOR_GREEN, COLOR_BLACK );
    init_pair ( 8, COLOR_YELLOW, COLOR_BLACK );
    init_pair ( 9, COLOR_GREEN, COLOR_BLACK );
    init_pair ( 10, COLOR_MAGENTA, COLOR_BLACK );
    init_pair ( 11, COLOR_CYAN, COLOR_BLACK );
    init_pair ( 12, COLOR_MAGENTA, COLOR_CYAN );
    init_pair ( 13, COLOR_YELLOW, COLOR_WHITE );
    init_pair ( 14, COLOR_WHITE, COLOR_BLACK );
    init_pair ( 15, COLOR_WHITE, COLOR_BLACK );
    init_pair ( 16, COLOR_CYAN, COLOR_BLACK );
    init_pair ( 17, COLOR_GREEN, COLOR_BLACK );
    init_pair ( 18, COLOR_WHITE, COLOR_GREEN );
    init_pair ( 19, COLOR_WHITE, COLOR_BLUE );
    init_pair ( 20, COLOR_RED, COLOR_YELLOW );

}

void print_border ( int y1, int x1, int y2, int x2 )
{
    int i;
    attron ( COLOR_PAIR ( 6 ) );
    move ( y1, x1 );
    addch ( ACS_ULCORNER );
    move ( y1, x2 );
    addch ( ACS_URCORNER );
    move ( y2, x1 );
    addch ( ACS_LLCORNER );
    move ( y2, x2 );
    addch ( ACS_LRCORNER );
    for ( i = x1 + 1; i <= x2 - 1; i++ )
    {
        move ( y1, i );
        addch ( ACS_HLINE );
        move ( y2, i );
        addch ( ACS_HLINE );
    }
    for ( i = y1 + 1; i <= y2 - 1; i++ )
    {
        move ( i, x1 );
        addch ( ACS_VLINE );
        move ( i, x2 );
        addch ( ACS_VLINE );
    }
    attroff ( COLOR_PAIR ( 6 ) );
    refresh ( );
}

void print_player_tank ( Tank * this )
{
    int y = this -> x + MAP_OFFSET_X, x = this -> y + MAP_OFFSET_Y;
    if ( this -> invulnerable > 0 ) if ( this -> invulnerable % 13 == 3 ) attron ( A_BLINK );
    attron ( A_BOLD );
    attron ( COLOR_PAIR ( 8 ) );
    switch ( this -> dir )
    {
    case UP:
        move ( y, x );
        printw ( "%c", 35 ); addch(ACS_VLINE); printw( "%c", 35 );
        move ( y + 1, x );
        printw("%c",35); addch(ACS_BLOCK); printw( "%c", 35 );
        move ( y + 2, x );
        printw("%c",35); printw(" "); printw( "%c", 35 );
        break;
    case DOWN:
        move ( y, x );
        printw ( "%c", 35 ); printw(" "); printw( "%c", 35 );
        move ( y + 1, x );
        printw ( "%c", 35 ); addch(ACS_BLOCK); printw ( "%c", 35 );
        move ( y + 2, x );
        printw ( "%c", 35 ); addch(ACS_VLINE); printw ( "%c", 35 );
        break;
    case LEFT:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        addch ( ACS_HLINE ); addch ( ACS_BLOCK ); printw ( " " );
        move ( y + 2, x );
        printw ( "###" );
        break;
    case RIGHT:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( " " ); addch ( ACS_BLOCK ); addch ( ACS_HLINE );
        move ( y + 2, x );
        printw ( "###" );
        break;
    }
    attroff ( COLOR_PAIR ( 8 ) );
    attroff ( A_BOLD );
    if ( this -> invulnerable > 0 ) if ( this -> invulnerable % 13 == 3 ) attroff ( A_BLINK );
    if ( this -> invulnerable > 0 ) this -> invulnerable--;
}

void print_armor_tank ( int dir, int y, int x, int hit_points )
{
    attron ( A_BOLD );
    switch ( hit_points )
    {
    case 1:
        attroff ( A_BOLD );
        attron ( COLOR_PAIR ( 14 ) );
        break;
    case 2:
        attron ( COLOR_PAIR ( 15 ) );
        break;
    case 3:
        attron ( COLOR_PAIR ( 16 ) );
        break;
    case 4:
        attron ( COLOR_PAIR ( 17 ) );
        break;
    }
    switch ( dir )
    {
    case UP:
        move ( y, x );
        printw ( "*" ); addch ( ACS_VLINE ); printw ( "*" );
        move ( y + 1, x );
        printw ( "*" ); addch ( ACS_BLOCK );printw ( "*" );
        move ( y + 2, x );
        printw ( "* *" );
        break;
    case DOWN:
        move ( y, x );
        printw ( "* *" );
        move ( y + 1, x );
        printw ( "*" ); addch ( ACS_BLOCK ); printw ( "*" );
        move ( y + 2, x );
        printw ( "*" ); addch ( ACS_VLINE ); printw ( "*" );
        break;
    case LEFT:
        move ( y, x );
        printw ( "***" );
        move ( y + 1, x );
        addch ( ACS_HLINE ); addch ( ACS_BLOCK ); printw ( " " );
        move ( y + 2, x );
        printw ( "***" );
        break;
    case RIGHT:
        move ( y, x );
        printw ( "***" );
        move ( y + 1, x );
        printw(" "); addch ( ACS_BLOCK ); addch ( ACS_HLINE );
        move ( y + 2, x );
        printw ( "***" );
        break;
    }
    switch ( hit_points )
    {
    case 1:
        attroff ( COLOR_PAIR ( 14 ) );
        break;
    case 2:
        attroff ( COLOR_PAIR ( 15 ) );
        attron ( A_BOLD );
        break;
    case 3:
        attroff ( COLOR_PAIR ( 16 ) );
        break;
    case 4:
        attroff ( COLOR_PAIR ( 17 ) );
        break;
    }
    attroff(A_BOLD);
}

void print_fast_tank ( int dir, int y, int x )
{
    attron ( A_BOLD );
    attron ( COLOR_PAIR ( 8 ) );
    switch ( dir )
    {
    case UP:
        move ( y, x );
        printw (" "); addch ( ACS_VLINE ); printw ( " " );
        move ( y + 1, x );
        printw ( "#" ); addch ( ACS_BLOCK ); printw ( "#" );
        move ( y + 2, x );
        printw ( "#" ); printw ( " " ); printw ( "#" );
        break;
    case DOWN:
        move ( y, x );
        printw ( "#" ); printw ( " " ); printw ( "#" );
        move ( y + 1, x );
        printw ( "#" ); addch ( ACS_BLOCK ); printw ( "#" );
        move ( y + 2, x );
        printw ( " " ); addch ( ACS_VLINE ); printw ( " " );
        break;
    case LEFT:
        move ( y, x );
        printw ( " " );
        printw ( "#" );
        printw ( "#" );
        move ( y + 1, x );
        addch ( ACS_HLINE ); addch ( ACS_BLOCK ); printw ( " " );
        move ( y + 2, x );
        printw ( " " );
        printw ( "#" );
        printw ( "#" );
        break;
    case RIGHT:
        move ( y, x );
        printw ( "#" );
        printw ( "#" );
        move ( y + 1, x );
        printw ( " " ); addch ( ACS_BLOCK ); addch ( ACS_HLINE  );
        move ( y + 2, x );
        printw ( "#" );
        printw ( "#" );
        break;
    }
    attroff ( COLOR_PAIR ( 8 ) );
    attroff ( A_BOLD );
}

void print_power_tank ( int dir, int y, int x )
{
    attron ( A_BOLD );
    attron ( COLOR_PAIR ( 8 ) );
    switch ( dir )
    {
    case UP:
        move ( y, x );
        printw ( "%c", 35 ); addch ( ACS_VLINE ); attron ( A_BOLD ); printw ( "%c", 35 );
        move ( y + 1, x );
        printw ( "%c", 35 ); addch ( ACS_BLOCK ); printw( "%c", 35 );
        move ( y + 2, x );
        printw ( "%c", 35 ); addch ( ACS_BLOCK ); printw( "%c", 35 );
        break;
    case DOWN:
        move ( y, x );
        printw ( "%c", 35 ); addch ( ACS_BLOCK ); printw ( "%c", 35 );
        move ( y + 1, x );
        printw ( "%c", 35 ); addch ( ACS_BLOCK ); printw ( "%c", 35 );
        move ( y + 2, x );
        printw ( "%c", 35 ); addch ( ACS_VLINE ); printw ( "%c", 35 );
        break;
    case LEFT:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        addch ( ACS_HLINE ); addch ( ACS_BLOCK ); addch ( ACS_BLOCK );
        move ( y + 2, x );
        printw ( "###" );
        break;
    case RIGHT:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        addch ( ACS_BLOCK ); addch ( ACS_BLOCK ); addch ( ACS_HLINE );
        move ( y  + 2, x );
        printw ( "###" );
        break;
    }
    attroff ( COLOR_PAIR ( 8 ) );
    attroff ( A_BOLD );
}

void print_basic_tank ( int dir, int y, int x )
{
    attron ( A_BOLD );
    switch ( dir )
    {
    case UP:
        move ( y, x );
        printw ( "%c", 35 ); addch(ACS_VLINE); printw( "%c", 35 );
        move ( y + 1, x );
        printw("%c",35); addch(ACS_BLOCK); printw( "%c", 35 );
        move ( y + 2, x );
        printw("%c",35); printw(" "); printw( "%c", 35 );
        break;
    case DOWN:
        move ( y, x );
        printw ( "%c", 35 ); printw(" "); printw( "%c", 35 );
        move ( y + 1, x );
        printw ( "%c", 35 ); addch(ACS_BLOCK); printw ( "%c", 35 );
        move ( y + 2, x );
        printw ( "%c", 35 ); addch(ACS_VLINE); printw ( "%c", 35 );
        break;
    case LEFT:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        addch ( ACS_HLINE ); addch ( ACS_BLOCK ); printw ( " " );
        move ( y + 2, x );
        printw ( "###" );
        break;
    case RIGHT:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( " " ); addch ( ACS_BLOCK ); addch ( ACS_HLINE );
        move ( y + 2, x );
        printw ( "###" );
        break;
    }
    attroff ( A_BOLD );
}

void print_tank ( Tank * this )
{
    this -> animation_counter = ( this -> animation_counter + 1 ) % 3;
    if ( this -> player ) print_player_tank ( this );
    else
    {
        if ( this -> power_type != NORMAL && this -> animation_counter >= 1 && this -> animation_counter <= 2 ) attron ( A_BLINK );
        switch ( this -> type )
        {
        case BASIC_TANK:
            print_basic_tank ( this -> dir, this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
            break;
        case FAST_TANK:
            print_fast_tank ( this -> dir, this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
            break;
        case POWER_TANK:
            print_power_tank ( this -> dir, this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
            break;
        case ARMOR_TANK:
            print_armor_tank ( this -> dir, this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y, this -> hit_points );
            break;
        }
        if ( this -> power_type != NORMAL && this -> animation_counter >= 1 && this -> animation_counter <= 2 ) attroff ( A_BLINK );
    }
}

void print_empty ( int y, int x )
{
    move ( y, x );
    printw ( " " );
}

void print_bullet ( int y, int x, int origin )
{
    if ( origin == 1 ) attron ( COLOR_PAIR ( 8 ) );
    attron ( A_BOLD );
    if ( map[y][x] == GRASS ) attron ( COLOR_PAIR ( 18 ) );
    if ( map[y][x] == WATER ) attron ( COLOR_PAIR ( 19 ) );
    move ( y, x );
    addch ( ACS_DIAMOND );
    if ( map[y][x] == WATER ) attroff ( COLOR_PAIR ( 19 ) );
    if ( map[y][x] == GRASS ) attroff ( COLOR_PAIR ( 18 ) );
    attroff ( A_BOLD );
    if ( origin == 1 ) attroff ( COLOR_PAIR ( 8 ) );
}

void print_grass ( int y, int x )
{
    attron ( A_REVERSE );
    move ( y, x );
    attron ( COLOR_PAIR ( 7 ) );
    addch ( ACS_CKBOARD );
    attroff ( COLOR_PAIR ( 7 ) );
    attroff ( A_REVERSE );
}

void print_water ( int y, int x )
{
    attron ( A_BOLD );
    move ( y, x );
    attron ( COLOR_PAIR ( 1 ) );
    if ( rand ( ) % 2 ) printw ( " " );
    else printw("~");
    attroff ( ( COLOR_PAIR ( 1 ) ) );
    attroff ( A_BOLD );
}

void print_brick ( int y, int x )
{
    attron ( A_BOLD );
    move ( y, x );
    attron ( COLOR_PAIR ( 2 ) );
    addch ( ACS_PLUS );
    attroff ( COLOR_PAIR ( 2 ) );
    attroff ( A_BOLD );
}

void print_steel(int y, int x)
{
    attron(A_STANDOUT);
    move(y, x);
    attron(COLOR_PAIR(3));
    addch(ACS_LANTERN);
    attroff((COLOR_PAIR(3)));
    attroff(A_STANDOUT);
}

void print_explosion(int y, int x)
{
    attron(A_BOLD);
    move(y, x);
    attron(COLOR_PAIR(20));
    printw("*");
    attroff((COLOR_PAIR(20)));
    attroff(A_BOLD);
    //refresh();
}

void print_field ( int y, int x, int type )
{
    switch ( type )
    {
    case EXPLOSION:
        print_explosion( y + MAP_OFFSET_X, x + MAP_OFFSET_Y );
        break;
    case EMPTY:
        print_empty ( y + MAP_OFFSET_X, x + MAP_OFFSET_Y );
        break;
    case BRICK:
        print_brick ( y + MAP_OFFSET_X, x + MAP_OFFSET_Y );
        break;
    case WATER:
        print_water ( y + MAP_OFFSET_X, x + MAP_OFFSET_Y );
        break;
    case GRASS:
        print_grass ( y + MAP_OFFSET_X, x + MAP_OFFSET_Y );
        break;
    case STEEL:
        print_steel ( y + MAP_OFFSET_X, x + MAP_OFFSET_Y );
        break;
    }
}

void print_bomb ( int y, int x )
{
    attron ( A_BOLD );
    attron ( COLOR_PAIR ( 13 ) );
    move ( y, x );
    printw ( " * " );
    move ( y + 1, x );
    attron ( COLOR_PAIR ( 3 ) );
    printw ( " " );
    addch ( ACS_DIAMOND );
    printw ( " " );
    move ( y + 2, x );
    printw ( "   " );
    attroff ( COLOR_PAIR ( 3 ) );
    attroff ( COLOR_PAIR ( 13 ) );
    attroff ( A_BOLD );
}

void print_helmet ( int y, int x )
{
    attron ( A_REVERSE );
    attron ( COLOR_PAIR ( 7 ) );
    move ( y, x );
    addch ( ACS_ULCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_URCORNER );
    move ( y + 1, x );
    addch ( ACS_VLINE );
    printw ("H");
    addch ( ACS_VLINE );
    move ( y + 2, x );
    addch ( ACS_LLCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_LRCORNER );
    attroff ( COLOR_PAIR ( 7 ) );
    attroff ( A_REVERSE );
    //refresh ( );
}

void print_star ( int y, int x )
{
    attron ( A_REVERSE );
    attron ( COLOR_PAIR ( 8 ) );
    move ( y, x );
    addch ( ACS_ULCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_URCORNER );
    move ( y + 1, x );
    addch ( ACS_VLINE );
    printw ( "%c", '*' );
    addch ( ACS_VLINE );
    move ( y + 2, x );
    addch ( ACS_LLCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_LRCORNER );
    attroff ( COLOR_PAIR ( 8 ) );
    attroff ( A_REVERSE );
}

void print_shovel ( int y, int x )
{
    attron ( A_BOLD );
    move ( y, x );
    printw ( "  #" );
    move ( y + 1, x );
    printw ( " / " );
    move ( y + 2, x );
    printw ( "O  " );
    attroff ( A_BOLD );
}

void print_timer ( int y, int x )
{
    attron ( A_REVERSE );
    attron ( COLOR_PAIR ( 10 ) );
    move ( y, x );
    addch ( ACS_ULCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_URCORNER );
    move ( y + 1, x );
    addch ( ACS_VLINE );
    attron ( A_ALTCHARSET );
    addch ( 167 );
    attroff ( A_ALTCHARSET );
    addch ( ACS_VLINE );
    move ( y + 2, x );
    addch ( ACS_LLCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_LRCORNER );
    attroff ( COLOR_PAIR ( 10 ) );
    attroff ( A_REVERSE );
}

void print_life ( int y, int x )
{
    attron ( COLOR_PAIR ( 0 ) );
    attron ( A_BOLD );
    move ( y, x );
    printw ( "   " );
    move ( y + 1, x );
    printw ( " O-" );
    move ( y + 2, x );
    printw ( "OOO" );
    attroff ( A_BOLD );
    attroff ( COLOR_PAIR ( 0 ) );
}

void print_power ( Power * this )
{
    this -> state = ( this -> state + 1 ) % 13;
    if ( this -> state >= 3 && this -> state <= 6 ) attron ( A_BLINK );
    switch ( this -> type)
    {
    case NORMAL:
        break;
    case BOMB:
        print_bomb ( this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
        break;
    case HELMET:
        print_helmet ( this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
        break;
    case SHOVEL:
        print_shovel ( this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
        break;
    case STAR:
        print_star ( this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
        break;
    case LIFE:
        print_life ( this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
        break;
    case TIMER:
        print_timer ( this -> x + MAP_OFFSET_X, this -> y + MAP_OFFSET_Y );
        break;
    }
    if ( this -> state >= 3 && this -> state <= 6 ) attroff ( A_BLINK );
}

void print_base ( int y, int x )
{
    attron ( COLOR_PAIR ( 4 ) );
    move ( y, x );
    addch ( ACS_ULCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_URCORNER );
    move ( y + 1, x );
    addch ( ACS_VLINE );
    attron ( COLOR_PAIR ( 5 ) );
    attron ( A_ALTCHARSET );
    addch ( 165 );
    attroff ( A_ALTCHARSET );
    attron( COLOR_PAIR( 4 ) );
    addch ( ACS_VLINE );
    move ( y + 2, x );
    addch ( ACS_LLCORNER );
    addch ( ACS_HLINE );
    addch ( ACS_LRCORNER );
    attroff ( COLOR_PAIR ( 4 ) );
}

void load_map ( char * input_file_name )
{
    int i, j;
    char buffer;
    FILE * input_file = fopen(input_file_name, "r");
    for (i = 0; i < MAP_SIZE; i++)
    {
        for (j = 0; j < MAP_SIZE; j++)
        {
            fscanf(input_file, "%c", &map[i][j]);
        }
        fscanf(input_file, "%c", &buffer);
    }
    for ( i = 0; i < TANKS_PER_LEVEL; i++ ) fscanf ( input_file, "%d", &levelConfiguration[i] );
    fclose ( input_file );
}

void print_map ( void )
{
    int i, j, k;
    base_x = -1;
    base_y = -1;
    print_border(MAP_OFFSET_X-1, MAP_OFFSET_Y-1, MAP_OFFSET_X + MAP_SIZE, MAP_OFFSET_Y + MAP_SIZE);
    for ( i = 0; i < MAP_SIZE; i++ )
        for ( j = 0; j < MAP_SIZE; j++ )
        {
            switch ( map[i][j] )
            {
                case EXPLOSION:
                {
                    print_field( i, j, EXPLOSION );
                    break;
                }
                case EMPTY:
                case BRICK:
                case WATER:
                case GRASS:
                case STEEL:
                    print_field ( i, j, map[i][j] );
                    break;
                case BASE:
                    if ( base_x == -1 ) base_x = i, base_y = j;
                    break;

            }
        }

    print_power(&power_up);
    print_tank ( &player1 );
    print_base ( base_x + MAP_OFFSET_X, base_y + MAP_OFFSET_Y );
    for ( i = 0; i < MAX_SPRITES; i++ )
    {
        if ( tanks[i].alive == false ) continue;
        print_tank ( &tanks[i] );
    }
    for ( i = 0; i < MAX_SPRITES; i++ )
    {
        if ( bullets[i].alive == false ) continue;
        print_bullet ( bullets[i].x + MAP_OFFSET_X, bullets[i].y + MAP_OFFSET_Y, bullets[i].source );
    }
    refresh ( );
}

void print_start_level_screen ( int level )
{
    attron ( A_BOLD );
    sound_start_music();
    char message[42], buffer[42];
    int i, j, size, curr_x, curr_y;
    strcpy ( message, "STAGE " );
    itoa ( level, buffer, 10 );
    strcat ( message, buffer );
    erase ( );
    print_border ( MAP_OFFSET_X - 1, MAP_OFFSET_Y - 1, MAP_OFFSET_X + MAP_SIZE, MAP_OFFSET_Y + MAP_SIZE );
    curr_x = MAP_OFFSET_X + MAP_SIZE / 2;
    curr_y = MAP_OFFSET_Y;
    size = strlen ( message );
    for ( j = 0; j + size < MAP_SIZE; j++ )
    {
        move ( curr_x, curr_y );
        for ( i = 0; i < MAP_SIZE; i++ ) printw( "*" );
        if ( j )
        {
            move ( curr_x + 1, curr_y + j - 1 );
            printw ( " " );
            refresh ( );
        }
        move ( curr_x + 1, curr_y + j );
        printw ( "%s", message );
        move ( curr_x + 2, curr_y );
        for ( i = 0; i < MAP_SIZE; i++ ) printw( "*" );
        refresh ( );
        Sleep ( 128 );
    }
    attroff ( A_BOLD );
}

void print_end_level_screen ( int level )
{
    attron ( A_BOLD );
    char message[42], buffer[42];
    int i, j, size, curr_x, curr_y;
    strcpy ( message, "STAGE " );
    itoa ( level, buffer, 10 );
    strcat ( message, buffer );
    strcat ( message, " COMPLETE!!!" );
    erase ( );
    print_border ( MAP_OFFSET_X - 1, MAP_OFFSET_Y - 1, MAP_OFFSET_X + MAP_SIZE, MAP_OFFSET_Y + MAP_SIZE );
    curr_x = MAP_OFFSET_X + MAP_SIZE / 2;
    curr_y = MAP_OFFSET_Y;
    size = strlen ( message );
    for ( j = 0; j + size < MAP_SIZE; j++ )
    {
        move ( curr_x, curr_y );
        for ( i = 0; i < MAP_SIZE; i++ ) printw( "*" );
        if ( j )
        {
            move ( curr_x + 1, curr_y + j - 1 );
            printw ( " " );
            refresh ( );
        }
        move ( curr_x + 1, curr_y + j );
        printw ( "%s", message );
        move ( curr_x + 2, curr_y );
        for ( i = 0; i < MAP_SIZE; i++ ) printw( "*" );
        refresh ( );
        Sleep ( 128 );
    }
    attroff ( A_BOLD );
}

void print_end_game_screen ( void )
{
    sound_end();
}

void print_empty_tank(int y, int x)
{
    move ( y, x );
    printw ( "   " );
    move ( y + 1, x );
    printw ("   ");
    move ( y + 2, x );
    printw ( "   " );
}

void print_digit ( int y, int x, int digit )
{
    attron ( A_BOLD );
    switch ( digit )
    {
    case 0:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "# #" );
        move ( y + 2, x );
        printw ( "# #" );
        move ( y + 3, x );
        printw ( "# #" );
        move ( y + 4, x );
        printw ( "###" );
        break;
    case 1:
        move ( y, x );
        printw ( "  #" );
        move ( y + 1, x );
        printw ( "  #" );
        move ( y + 2, x );
        printw ( "  #" );
        move ( y + 3, x );
        printw ( "  #" );
        move ( y + 4, x );
        printw ( "  #" );
        break;
    case 2:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "  #" );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "#  " );
        move ( y + 4, x );
        printw ( "###" );
        break;
    case 3:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "  #" );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "  #");
        move ( y + 4, x );
        printw ( "###" );
        break;
    case 4:
        move ( y, x );
        printw ( "# #" );
        move ( y + 1, x );
        printw ( "# #" );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "  #" );
        move ( y + 4, x );
        printw ( "  #" );
        break;
    case 5:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "#  " );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "  #" );
        move ( y + 4, x );
        printw ( "###" );
        break;
    case 6:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "#  " );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "# #" );
        move ( y + 4, x );
        printw ( "###" );
        break;
    case 7:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "  #" );
        move ( y + 2, x );
        printw ( "  #" );
        move ( y + 3, x );
        printw ( "  #" );
        move ( y + 4, x );
        printw ( "  #" );
        break;
    case 8:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "# #" );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "# #" );
        move ( y + 4, x );
        printw( "###" );
        break;
    case 9:
        move ( y, x );
        printw ( "###" );
        move ( y + 1, x );
        printw ( "# #" );
        move ( y + 2, x );
        printw ( "###" );
        move ( y + 3, x );
        printw ( "  #" );
        move ( y + 4, x );
        printw ("  #" );
        break;
    }
    attroff ( A_BOLD );
}

void print_indicators ( int totalSpawned, int lives, int stars, int score )
{
    int i, j, currX = MAP_OFFSET_X, currY = MAP_OFFSET_Y + MAP_SIZE + 5;
    for ( i = 0; i < TANKS_PER_LEVEL / 2; i++ )
    {
        for ( j = 0; j < 2; j++ )
        {
            if ( i * 2 + j >= TANKS_PER_LEVEL - totalSpawned ) print_empty_tank ( currX, currY + j * 4 );
            else
            {
                Tank temp;
                temp.x = currX - MAP_OFFSET_X;
                temp.y = currY + j * 4 - MAP_OFFSET_Y;
                temp.dir = DOWN;
                temp.player = false;
                temp.animation_counter = 0;
                temp.power_type = NORMAL;
                temp.type = levelConfiguration[TANKS_PER_LEVEL - 1 - i * 2 - j];
                print_tank ( &temp );
            }
        }
        currX += 4;
    }
    currX = MAP_OFFSET_X;
    currY = MAP_OFFSET_Y + MAP_SIZE + 15;
    move ( currX, currY );
    attron ( A_BOLD );
    printw ( "1P" );
    attroff ( A_BOLD );
    Tank P1;
    P1.x = currX + 2 - MAP_OFFSET_X, P1.y = currY - MAP_OFFSET_Y, P1.dir = UP;
    P1.invulnerable = 0;
    print_player_tank ( &P1 );
    print_digit ( currX, currY + 4, lives );
    currX += 6;
    print_star ( currX + 2, currY );
    print_digit ( currX, currY + 4, stars );
}

void kill_curses ( void )
{
    endwin ( );
}

