#include "global.h"

int gameOver;
int gameDifficulty;
char characterMap[] = { '.', 'B', 'S', 'W', 'G', 'X', 'T' };
char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE];
int mapUsed[MAP_SIZE][MAP_SIZE];
int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;
int totalSpawned;
int power_indexes[] = {4, 11, 18};
Power power_up;
//configuration for difficulty
const Difficulty confDiff[3] = {{SPAWNSPEED_EASY,ENEMYSHOOTSPEED_EASY,get_decision_easy},{SPAWNSPEED_MEDIUM,ENEMYSHOOTSPEED_MEDIUM,get_decision_medium},{SPAWNSPEED_HARD,ENEMYSHOOTSPEED_HARD,get_decision_hard}};

char mainMenu[][100] = {{"Start Game"}, {"Edit Level"}, {"Show High Scores"}, {"Exit Game"}};
char levels[][100] = {{"Level  1"}, {"Level  2"}, {"Level  3"}, {"Level  4"}, {"Level  5"}, {"Level  6"}, {"Level  7"}, {"Level  8"}, {"Level  9"}, {"Level 10"}, {"Level 11"}, {"Level 12"}, {"Level 13"}, {"Level 14"}, {"Level 15"}, {"Level 16"}, {"Level 17"},
                      {"Level 18"}, {"Level 19"}, {"Level 20"}, {"Level 21"}, {"Level 22"}, {"Level 23"}, {"Level 24"}, {"Level 25"},
                      {"Level 26"}, {"Level 27"}, {"Level 28"}, {"Level 29"}, {"Level 30"},
                      {"Level 31"}, {"Level 32"}, {"Level 33"}, {"Level 34"}, {"Level 35"}};
char difficulties[][100] = {{"Easy"}, {"Medium"}, {"Hard"}};
char highScores[20][100];

char levelName[100], buffer[100];

int read_input(){
#ifdef _WIN32
    return getch();
#else
    return getchar();
#endif // _WIN32
}
#include <mmsystem.h>
int main(int argc, char **argv)
{
    int menu_choice, level, difficulty = 0;
    setlocale (LC_CTYPE, "");
    srand(time(NULL));
    init_curses();
    resize_term(80,80);
    print_life(50,10);
    while ( 1 )
    {
        menu_choice = print_menu (2, 5, 4, 15, "Battle Tank - MAIN MENU", mainMenu, 1);
        if (menu_choice == 0)
        {
            erase();
            difficulty = print_menu(2, 5, 3, 15, "SELECT DIFFICULTY", difficulties, 1);
            erase();
            startGame(difficulty);
        }
        if (menu_choice == 1)
        {
            erase();
            level = print_menu (2, 5, 35, 15, "SELECT LEVEL", levels, 1) + 1;
            erase();
            load_editor(level);
         }
        if (menu_choice == 2)
        {
            int i;
            char ch;
            FILE * high_scores_file = fopen ( "high_scores.txt", "r" );
            for (i = 0; i < 20; i++)
            {
                fgets(highScores[i], 100, high_scores_file);
                ch = highScores[i][strlen(highScores[i]) - 1];
                if (ch == '\n' || ch == '\r') highScores[i][strlen(highScores[i]) - 1] = '\0';
            }
            erase();
            i = print_menu (2, 5, 20, 15, "PRESS ENTER TO RETURN", highScores, 1);
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
