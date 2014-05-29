//windows only
#ifdef _WIN32
#include <curses.h>
#endif

//linux only
#ifndef _WIN32
#include <ncurses.h>
#include "kbhit_linux.h"
#endif


#include <time.h>

#include "global.h"
#include "kletve.h"
#include "editor.h"
#include "engine.h"
#include "gameloop.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    init_curses();


    load_editor();
//    getch();
//    load_map("Level0x01.map");
//    print_map();
    chose_level();
    getch();
    kill_curses();

    return 0;
}
