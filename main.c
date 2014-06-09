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
const difficultyConfig confDiff[3] = {{SPAWNSPEED_EASY,ENEMYSHOOTSPEED_EASY,get_decision_easy},{SPAWNSPEED_MEDIUM,ENEMYSHOOTSPEED_MEDIUM,get_decision_medium},{SPAWNSPEED_HARD,ENEMYSHOOTSPEED_HARD,get_decision_hard}};

char main_menu[][100] = {{"Start Game"}, {"Edit Level"}, {"Show High Scores"}, {"Exit Game"}};
char levels[][100] = {{"Level 0"}, {"Level 1"}, {"Level 2"}, {"Level 3"}, {"Level 4"}, {"Level 5"}, {"Level 6"}, {"Level 7"}, {"Level 8"}, {"Level 9"}, {"Return"}};
char difficulties[][100] = {{"Easy"}, {"Medium"}, {"Hard"}};
char high_scores[20][100];

char level_name[100] = "Level0x0.map";

int read_input(){
#ifdef _WIN32
    return getch();
#else
    return getchar();
#endif // _WIN32
}


int main(int argc, char **argv)
{
    int menu_choice, level, difficulty = 0;
    setlocale (LC_CTYPE, "");
    srand(time(NULL));
    init_curses();
    while ( 1 )
    {
        menu_choice = print_menu (2, 5, 4, 15, "Battle Tank - MAIN MENU", main_menu, 1);
        if (menu_choice == 0)
        {
            erase();
            level = print_menu (2, 5, 10, 15, "SELECT LEVEL", levels, 1);
            erase();
            difficulty = print_menu(2, 5, 3, 15, "SELECT DIFFICULTY", difficulties, 1);
            erase();
            level_name[7] = '0' + level;
            start_game(level_name, difficulty);
        }
        if (menu_choice == 1)
        {
            erase();
            level = print_menu (2, 5, 10, 15, "SELECT LEVEL", levels, 1);
            erase();
            level_name[7] = '0' + level;
            load_editor(level_name);
        }
        if (menu_choice == 2)
        {
            int i;
            char ch;
            FILE * high_scores_file = fopen ( "high_scores.txt", "r" );
            for (i = 0; i < 20; i++)
            {
                fgets(high_scores[i], 100, high_scores_file);
                ch = high_scores[i][strlen(high_scores[i]) - 1];
                if (ch == '\n' || ch == '\r') high_scores[i][strlen(high_scores[i]) - 1] = '\0';
            }
            erase();
            i = print_menu (2, 5, 20, 15, "PRESS ENTER TO RETURN", high_scores, 1);
        }
        if (menu_choice == 3)
        {
            kill_curses();
            return 0;
        }
        erase();
    }
    return 0;
}
