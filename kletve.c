#include "global.h"

void init_curses(void)
{
    #ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	#endif

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
	curs_set(0);
    init_colors();
}

void init_colors(void)
{
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_YELLOW, COLOR_RED);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
    init_pair(9, COLOR_GREEN, COLOR_BLACK);
    init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(11, COLOR_CYAN, COLOR_BLACK);
    init_pair(13,COLOR_YELLOW,COLOR_WHITE);
}

void print_border(int y1, int x1, int y2, int x2)
{
    int i;
    attron(COLOR_PAIR(6));
    move(y1, x1);
    addch(ACS_ULCORNER);
    move(y1, x2);
    addch(ACS_URCORNER);
    move(y2, x1);
    addch(ACS_LLCORNER);
    move(y2, x2);
    addch(ACS_LRCORNER);
    for (i = x1 + 1; i <= x2 - 1; i++)
    {
        move(y1, i);
        addch(ACS_HLINE);
        move(y2, i);
        addch(ACS_HLINE);
    }
    for (i = y1 + 1; i <= y2 - 1; i++)
    {
        move(i, x1);
        addch(ACS_VLINE);
        move(i, x2);
        addch(ACS_VLINE);
    }
    attroff(COLOR_PAIR(6));
    refresh();
}

void print_tank(int dir, int y, int x)
{
    attron(COLOR_PAIR(8));
    switch (dir)
    {
    case UP:
        move(y, x);
        printw("%c",35);addch(ACS_VLINE);printw("%c",35);
        move(y + 1, x);
        printw("%c",35);addch(ACS_BLOCK);printw("%c",35);
        move(y + 2, x);
        printw("%c",35);printw(" ");printw("%c",35);
        break;
    case DOWN:
        move(y, x);
        printw("%c",35);printw(" ");printw("%c",35);
        move(y + 1, x);
        printw("%c",35);addch(ACS_BLOCK);printw("%c",35);
        move(y + 2, x);
        printw("%c",35);addch(ACS_VLINE);printw("%c",35);
        break;
    case LEFT:
        move(y, x);
        printw("%c%c%c",35,35,35);
        move(y + 1, x);
        addch(ACS_HLINE);addch(ACS_BLOCK);printw(" ");
        move(y + 2, x );
        printw("%c%c%c",35,35,35);
        break;
    case RIGHT:
        move(y, x);
        printw("%c%c%c",35,35,35);
        move(y + 1, x);
        printw(" ");addch(ACS_BLOCK);addch(ACS_HLINE);
        move(y + 2, x);
        printw("%c%c%c",35,35,35);
        break;
    }
    attroff(COLOR_PAIR(8));
}

void print_enemy_tank (int dir, int y, int x, int hit_points)
{
    switch (hit_points)
    {
    case 1:
        break;
    case 2:
        attron(COLOR_PAIR(9));
        break;
    case 3:
        attron(COLOR_PAIR(10));
        break;
    case 4:
        attron(COLOR_PAIR(11));
        break;
    }
    switch (dir)
    {
    case UP:
        move(y, x);
        printw("%c",35);addch(ACS_VLINE);printw("%c",35);
        move(y + 1, x);
        printw("%c",35);addch(ACS_BLOCK);printw("%c",35);
        move(y + 2, x);
        printw("%c",35);printw(" ");printw("%c",35);
        break;
    case DOWN:
        move(y, x);
        printw("%c",35);printw(" ");printw("%c",35);
        move(y + 1, x);
        printw("%c",35);addch(ACS_BLOCK);printw("%c",35);
        move(y + 2, x);
        printw("%c",35);addch(ACS_VLINE);printw("%c",35);
        break;
    case LEFT:
        move(y, x);
        printw("%c%c%c",35,35,35);
        move(y + 1, x);
        addch(ACS_HLINE);addch(ACS_BLOCK);printw(" ");
        move(y + 2, x );
        printw("%c%c%c",35,35,35);
        break;
    case RIGHT:
        move(y, x);
        printw("%c%c%c",35,35,35);
        move(y + 1, x);
        printw(" ");addch(ACS_BLOCK);addch(ACS_HLINE);
        move(y + 2, x);
        printw("%c%c%c",35,35,35);
        break;
    }
    switch ( hit_points )
    {
    case 1:
        break;
    case 2:
        attroff(COLOR_PAIR(9));
        break;
    case 3:
        attroff(COLOR_PAIR(10));
        break;
    case 4:
        attroff(COLOR_PAIR(11));
        break;
    }
}

void print_empty(int y, int x)
{
    move(y, x);
    printw(" ");
}

void print_bullet(int y, int x)
{
    move(y, x);
    addch(ACS_DIAMOND);
    refresh();
}

void print_grass(int y, int x)
{
    move(y, x);
    attron(COLOR_PAIR(7));
    addch(ACS_CKBOARD);
    attroff((COLOR_PAIR(7)));
}

void print_water(int y, int x)
{
    move(y, x);
    attron(COLOR_PAIR(1));
    addch(ACS_CKBOARD);
    attroff((COLOR_PAIR(1)));
}

void print_brick(int y, int x)
{
    move(y, x);
    attron(COLOR_PAIR(2));
    addch(ACS_PLUS);
    attroff((COLOR_PAIR(2)));
}

void print_steel(int y, int x)
{
    move(y, x);
    attron(COLOR_PAIR(3));
    addch(ACS_LANTERN);
    attroff((COLOR_PAIR(3)));
}

void print_bomb(int y, int x)
{
    attron(COLOR_PAIR(13));
    move(y, x);
    printw(" * ");
    move(y + 1, x);
    attron(COLOR_PAIR(3));
    printw(" ");
    addch(ACS_DIAMOND);
    printw(" ");
    move(y + 2, x);
    printw("   ");
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(13));
}

void print_star(int y, int x)
{
    attron(COLOR_PAIR(8));
    move(y, x);
    addch(ACS_ULCORNER);
    addch(ACS_HLINE);
    addch(ACS_URCORNER);
    move(y + 1, x);
    addch(ACS_VLINE);
    printw("%c",'*');
    addch(ACS_VLINE);
    move(y + 2, x);
    addch(ACS_LLCORNER);
    addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    attroff(COLOR_PAIR(8));
}

void print_shovel(int y, int x)
{
    attron(A_BLINK);
    attron(A_BOLD);
    move(y, x);
    printw("  #");
    move(y + 1, x);
    printw(" / ");
    move(y + 2, x);
    printw("O  ");
    attroff(A_BOLD);
    attroff(A_BLINK);
}

void print_timer_power_up(int y, int x)
{
    attron(COLOR_PAIR(10));
    move(y, x);
    addch(ACS_ULCORNER);
    addch(ACS_HLINE);
    addch(ACS_URCORNER);
    move(y + 1, x);
    addch(ACS_VLINE);
    attron(A_ALTCHARSET);
    printw("T");
    attroff(A_ALTCHARSET);
    addch(ACS_VLINE);
    move(y + 2, x);
    addch(ACS_LLCORNER);
    addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    attroff(COLOR_PAIR(10));
}

void print_tank_power_up(int y, int x)
{
    attron(COLOR_PAIR(0));
    attron(A_BOLD);
    move(y, x);
    printw("   ");
    move(y + 1, x);
    printw(" O-");
    move(y + 2, x);
    printw("OOO");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(0));
}

void print_power_up(Power powerUP)
{
    if ( powerUP.state == 3 ) attron(A_BLINK);
    switch ( powerUP.type )
    {
    case NORMAL:
        break;
    case BOMB:
        print_bomb(powerUP.x + MAP_OFFSET_X, powerUP.y + MAP_OFFSET_Y);
        break;
    case LIFE:
        print_tank_power_up(powerUP.x + MAP_OFFSET_X, powerUP.y + MAP_OFFSET_Y);
        break;
    }
    if ( powerUP.state == 3 ) attroff(A_BLINK);
    refresh();
}

void print_base(int y, int x)
{
    attron(COLOR_PAIR(4));
    move(y, x);
    addch(ACS_ULCORNER);
    addch(ACS_HLINE);
    addch(ACS_URCORNER);
    move(y + 1, x);
    addch(ACS_VLINE);
    attron(COLOR_PAIR(5));
    printw("B");
    attron(COLOR_PAIR(4));
    addch(ACS_VLINE);
    move(y + 2, x);
    addch(ACS_LLCORNER);
    addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(5));
}

void kill_curses(void)
{
    endwin();
}

void load_map(char * input_file_name)
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
    print_border(MAP_OFFSET_X-1, MAP_OFFSET_Y -1, MAP_OFFSET_X + MAP_SIZE, MAP_OFFSET_Y + MAP_SIZE);
}

void print_map(void)
{
    int i, j, dx, dy;
    base_x = -1;
    base_y = -1;
    for (i = 0; i < MAP_SIZE; i++)
        for (j = 0; j < MAP_SIZE; j++)
        {
            switch ( map[i][j] )
            {
                case EMPTY:
                    print_empty ( i + MAP_OFFSET_X, j + MAP_OFFSET_Y );
                    break;
                case BRICK:
                    print_brick ( i + MAP_OFFSET_X, j + MAP_OFFSET_Y );
                    break;
                case WATER:
                    print_water(i + MAP_OFFSET_X, j + MAP_OFFSET_Y);
                    break;
                case STEEL:
                    print_steel(i + MAP_OFFSET_X, j + MAP_OFFSET_Y);
                    break;
                case BASE:
                    if (base_x == -1) base_x = i, base_y = j;
            }
        }
    print_base(base_x + MAP_OFFSET_X, base_y + MAP_OFFSET_Y) ;
    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (tanks[i].alive == false) continue;
        print_enemy_tank(tanks[i].dir, tanks[i].x + MAP_OFFSET_X, tanks[i].y + MAP_OFFSET_Y, tanks[i].hit_points);
    }
    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (bullets[i].alive == false) continue;
        print_bullet(bullets[i].x + MAP_OFFSET_X,bullets[i].y + MAP_OFFSET_Y);
    }
    refresh();
}

void print_end_screen(void)
{
}
