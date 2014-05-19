#include <curses.h>
#include <time.h>

#include "global.h"
#include "kletve.h"
#include "editor.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    init_curses();

    print_border(MAP_OFFSET_X - 1, MAP_OFFSET_Y - 1, MAP_OFFSET_X + MAP_SIZE, MAP_OFFSET_Y + MAP_SIZE);
    load_editor();
    getch();
    load_map();
    print_map();
    getch();
    kill_curses();

    return 0;
}
