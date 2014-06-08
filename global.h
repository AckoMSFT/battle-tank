#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include <locale.h>
#include <time.h>

#ifdef _WIN32
#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <curses.h>

#define  DOWN 0
#define    UP 1
#define  LEFT 2
#define RIGHT 3

#define NEW_KEY_UP KEY_UP
#define NEW_KEY_DOWN KEY_DOWN
#define NEW_KEY_RIGHT KEY_RIGHT
#define NEW_KEY_LEFT KEYLEFT

#define MIN_KEY KEY_DOWN

#else
#include <ncurses.h>
#include "linux_spec.h"

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define NEW_KEY_UP 65
#define NEW_KEY_DOWN 66
#define NEW_KEY_RIGHT 67
#define NEW_KEY_LEFT 68

#define MIN_KEY NEW_KEY_UP

#endif



#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))


#define SPACE ' '

#define MAP_OFFSET_X 1
#define MAP_OFFSET_Y 1
#define MAP_SIZE 39

//map tile types
#define  TANK 'T'
#define  BASE 'X'
#define WATER 'W'
#define GRASS 'G'
#define EMPTY '.'
#define STEEL 'S'
#define BRICK 'B'
#define FRAME 'F'

//game config options
#define DEBUG 0
#define MAXSPRITES 20
#define FRAMES_PER_SEC 30
#define BULLETSPEED 3
#define SHOOTSPEED 15
#define TANKSPEED 15

//difficulty config
//easy
#define SPAWNSPEED_EASY 300
#define ENEMYSHOOTSPEED_EASY 200
#define RANDOM_EASY 1

//medium
#define SPAWNSPEED_MEDIUM 200
#define ENEMYSHOOTSPEED_MEDIUM 100
#define RANDOM_MEDIUM 0.5

//hard
#define SPAWNSPEED_HARD 100
#define ENEMYSHOOTSPEED_HARD 50
#define RANDOM_HARD 0

typedef struct
{
    int x, y, dir,val, shootState,moveState;
}Tank;



typedef struct
{
    int x, y, dir, state,val;
}Bullet;

typedef struct
{
    int spawn,shoot;
    int (*AI) ();
}difficultyConfig;

extern Tank tanks[ MAXSPRITES ];
extern Tank myTank;
extern Bullet bullets[ MAXSPRITES ];
extern int gameOver;
extern int gameDifficulty;
extern const difficultyConfig confDiff[3];
extern char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE], character_map[];
extern int mapUsed[MAP_SIZE][MAP_SIZE];
extern int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;

int read_input();

#include "kletve.h"
#include "editor.h"
#include "menu.h"
#include "engine.h"
#include "gameloop.h"
#endif // GLOBAL_H_INCLUDED
