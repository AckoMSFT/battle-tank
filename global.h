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
#define NEW_KEY_LEFT KEY_LEFT

#define MIN_KEY KEY_DOWN
#else
#include <ncurses.h>
#include "linux_spec.h"

#define    UP 0
#define  DOWN 1
#define RIGHT 2
#define  LEFT 3

#define    NEW_KEY_UP 65
#define  NEW_KEY_DOWN 66
#define NEW_KEY_RIGHT 67
#define  NEW_KEY_LEFT 68

#define MIN_KEY NEW_KEY_UP
#endif

#define bool int
#define true 1
#define false 0

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define SPACE ' '

#define MAP_OFFSET_X 1
#define MAP_OFFSET_Y 1
#define MAP_SIZE 39

#define NUMBER_OF_LEVELS 3
#define MAX_NUMBER_OF_TANKS 5
#define TANKS_PER_LEVEL 20

#define INVULNERABLE_SECS 5

// map tiles

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
#define MAX_SPRITES 128
#define FRAMES_PER_SEC 20
#define BULLET_SPEED 2
#define SHOOT_SPEED 10
#define TANK_SPEED 3
#define AI_SPEED 10


#define SPAWNSPEED_EASY 100
#define ENEMYSHOOTSPEED_EASY 200
#define BASE_EASY 0.1
#define MYTANK_EASY 0.1

//medium
#define SPAWNSPEED_MEDIUM 75
#define ENEMYSHOOTSPEED_MEDIUM 100
#define BASE_MEDIUM 0.3
#define MYTANK_MEDIUM 0.1

//hard
#define SPAWNSPEED_HARD 50
#define ENEMYSHOOTSPEED_HARD 50
#define BASE_HARD 0.5
#define MYTANK_HARD 0.5

typedef struct tank
{
    int x, y, dir, shoot_state, shoot_rate, move_state, move_rate, value, hit_points, stars, invulnerable;
    int AIDecisions[AI_SPEED],AIState;
    bool alive;
} Tank;

typedef struct bullet
{
    int x, y, dir, state, source;
    bool alive;
} Bullet;

typedef struct
{
    int type, x, y, state;
} Power;

typedef struct difficulty
{
    int spawn,shoot;
    int (*AI) ();
} Difficulty;

// types of tanks
enum { BASIC_TANK, FAST_TANK, POWER_TANK, ARMOR_TANK };
// types of power-ups
enum { NORMAL, BOMB, HELMET, SHOVEL, STAR, LIFE, TIMER };


int levelConfiguration[20];

// global variables
extern char characterMap[];

Tank tanks[MAX_SPRITES];
Tank player1, player2;
Bullet bullets[MAX_SPRITES];
extern int totalSpawned;
extern int gameDifficulty;
extern const Difficulty confDiff[3];
extern char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE];
extern int mapUsed[MAP_SIZE][MAP_SIZE];
extern int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size, numberOfTanks;

int myScore, gameOver, numberOfTanks;

int read_input();

#include "kletve.h"
#include "editor.h"
#include "menu.h"
#include "engine.h"
#include "gameloop.h"
#include "sound.h"
#include "stack.h"
#include "queue.h"
#endif // GLOBAL_H_INCLUDED
