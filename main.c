#include "global.h"
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

char main_menu_entries[][100] = {{"Start Game"}, {"Load Level"}, {"Edit Level"}, {"Exit Game"}};
char sub_menu_entries[][100] = {{"Level 0"}, {"Level 1"}, {"Level 2"}, {"Level 3"}, {"Level 4"}, {"Level 5"}, {"Level 6"}, {"Level 7"}, {"Level 8"}, {"Level 9"}, {"Return"}};
char level_name[100] = "Level0x .map";

int main(int argc, char **argv)
{
    int menu_choice, sub_menu_choice;
    setlocale (LC_CTYPE, "");
    srand(time(NULL));
    init_curses();

    while ( 1 )
    {
        menu_choice = print_menu (2, 5, 4, 15, "Battle Tank - MAIN MENU", main_menu_entries, menu_choice);

        // start the game
        if (menu_choice == 0)
        {
            choose_level(level_name);
            start_game();
        }

        // choose level
        if (menu_choice == 1)
        {
            sub_menu_choice = print_menu (6, 22, 10, 15, "SELECT LEVEL", sub_menu_entries, 1);
            level_name[7] = '0' + sub_menu_choice;
        }

        // edit level
        if (menu_choice == 2)
        {
            erase();
            load_editor(level_name);
        }

        // get me out of here
        if (menu_choice == 3)
        {
            kill_curses();
            return 0;
        }

        erase();
    }

    return 0;
}
