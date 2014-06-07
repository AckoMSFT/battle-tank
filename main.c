#include "global.h"
<<<<<<< HEAD
#include "kletve.h"
#include "editor.h"
#include "engine.h"
#include "gameloop.h"
#include "menu.h"

=======
>>>>>>> 2112711169df7651041c898a9ad1ce55ad25a88b
//GLOBALS

Tank tanks[ MAXSPRITES ];
Tank myTank = {35,12,1,1,0,0};
Bullet bullets[ MAXSPRITES ];

int gameOver;
int gameDifficulty;

char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE], character_map[] = { '.', 'B', 'S', 'W', 'X', 'T' };
int mapUsed[MAP_SIZE][MAP_SIZE];
int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;
//configuration for difficulty
const difficultyConfig confDiff[3] = {{SPAWNSPEED_EASY,ENEMYSHOOTSPEED_EASY},{SPAWNSPEED_MEDIUM,ENEMYSHOOTSPEED_MEDIUM},{SPAWNSPEED_HARD,ENEMYSHOOTSPEED_HARD}};

char main_menu_items[][100] = {{"Start Game"},     /* Every menu needs an */
                    {"Load Game"},     /* array like these to */
                    {"Quit Game"},};   /* hold the entries.   */
     char sub_menu_items[][100] = {{"Level 0"},
                         {"Level 1"},
                         {"Level 2"},
                         {"Level 3"},
                         {"Level 4"},
                         {"Level 5"},
                         {"Level 6"},
                         {"Level 7"},
                         {"Level 8"},
                         {"Level 9"},
                         {"Return"},};

int main(int argc, char **argv)
{
    int menu_ret = 1, menu_ret2 = 1;


    setlocale (LC_CTYPE, "");
    srand(time(NULL));
    init_curses();

 do  /* This loop terminates when MAIN MENU returns 3, Quit Game.   */
    {   /* menu_ret is sent as the start value, to make the last entry */
        /* highlighted when you return to the main menu.               */
        menu_ret = print_menu (2, 5, 3, 15,
                               "Battle Tank - MAIN MENU", main_menu_items, menu_ret);

        if (menu_ret == 1)  /* This is just an example program. */
        {                   /* You can't start an actual game.  */
            mvprintw (5, 23, "Lol jk! This is a demo program.");
            mvprintw (6, 26, "Press any key to return.");
            getch();
        }

        else if (menu_ret == 2) /* If you select load game, a new    */
        {                       /* menu will show up without erasing */
            do                  /* the main menu. */
            {
                menu_ret2 = print_menu (6, 22, 11, 15,
                                        "SELECT LEVEL", sub_menu_items, 1);
            }
            while (menu_ret2 != 11);
        }

        erase();    /* When you return from the SELECT SLOT menu,      */
    }               /* everything will be erased and MAIN MENU will be */
    while (menu_ret != 3); /* reprinted.                               */

    load_editor();
//    getch();
//    load_map("Level0x01.map");
//    print_map();
    choose_level();
    getch();
    kill_curses();

    return 0;
}
