#include <time.h>
#include <stdio.h>

//windows only

#include <curses.h>


//linux only
//#ifndef _WIN32
//#include <ncurses.h>
//#include "kbhit_linux.h"
//#endif


#include "global.h"
#include "kletve.h"
#include "editor.h"
#include "engine.h"
#include "gameloop.h"

//GLOBALS
Tank tanks[ MAXSPRITES ];
Tank myTank = {35,12,1,1,0,0};

Bullet bullets[ MAXSPRITES ];

int gameOver;
int gameDifficulty;

char map[MAP_SIZE+2][MAP_SIZE+2], editor[MAP_SIZE][MAP_SIZE], character_map[] = { '.', 'B', 'S', 'W', 'X', 'T' };
int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;
//configuration for difficulty
const difficultyConfig confDiff[3] = {{SPAWNSPEED_EASY,ENEMYSHOOTSPEED_EASY},{SPAWNSPEED_MEDIUM,ENEMYSHOOTSPEED_MEDIUM},{SPAWNSPEED_HARD,ENEMYSHOOTSPEED_HARD}};


int main(int argc, char **argv)
{
    srand(time(NULL));
    init_curses();


    load_editor();
//    getch();
//    load_map("Level0x01.map");
//    print_map();
    choose_level();
    getch();
    kill_curses();

    return 0;
}
