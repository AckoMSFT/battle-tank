/**
 *  @file gameloop.h
 *  @brief - Definicije globalnih struktura i konstanti, deklaracija globalnih promenljivih.
 */
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#ifdef _WIN32
#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <curses.h>
#include <mmsystem.h>

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

/**
 *  @brief - Ofset pri crtanju mape.
 */
#define MAP_OFFSET_X 1

/**
 *  @brief - Ofset pri crtanju mape.
 */
#define MAP_OFFSET_Y 1

/**
 *  @brief - Velicina mape.
 */
#define MAP_SIZE 39


/**
 *  @brief - Broj nivoa.
 */
#define NUMBER_OF_LEVELS 35

/**
 *  @brief - Maksimalni broj neprijateljskih tenkova koji se trenutno nalaze na mapi.
 */
#define MAX_NUMBER_OF_TANKS 5

/**
 *  @brief - Broj neprijateljskih tenkova po nivou.
 */
#define TANKS_PER_LEVEL 20

/**
 *  @brief - Broj sekundi koliko traje TIMER pojacanje.
 */
#define TIMER_SECS 15

/**
 *  @brief - Broj sekundi koliko traje SHOVEL pojacanje.
 */
#define SHOVEL_SECS 20

/**
 *  @brief - Broj sekundi koliko traje HELMET pojacanje.
 */
#define HELMET_SECS 15

/**
 *  @brief - Broj sekundi koliko traje pocetna neunistivost igraca.
 */
#define INVULNERABLE_SECS 5

#define INF 123454321


/**
 *  @brief - Parametar RSA enkripcije.
 */
#define RSA_N 3233

/**
 *  @brief - Parametar RSA enkripcije.
 */
#define RSA_E 17

/**
 *  @brief - Parametar RSA enkripcije.
 */
#define RSA_D 2753

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define  TANK 'T'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define  BASE 'X'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define WATER 'W'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define GRASS 'G'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define EMPTY '.'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define STEEL 'S'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define BRICK 'B'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define FRAME 'F'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define EXPLOSION 'E'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define EXPLOSION_GRASS 'Y'

/**
 *  @brief - Prikazivanje elemenata mape pomocu karaktera.
 */
#define EXPLOSION_WATER 'Z'

#define MAX_SPRITES 128
#define FRAMES_PER_SEC 30

#define BULLET_SPEED 2
#define SHOOT_SPEED 10
#define TANK_SPEED 3
#define ENEMYSPAWNRANDOM 25

#define AI_SPEED 7
#define AI_PARAM1 3
//how often should it shot ( ratio between shooting and moving )
#define AI_PARAM2 1
#define AI_PARAM3 1.1

#define SPAWNSPEED_EASY 160
#define ENEMYSHOOTSPEED_EASY 30
#define BASE_EASY 0.2
#define MYTANK_EASY 0.2
#define ENEMYMOVESPEED_EASY 9

//medium
#define SPAWNSPEED_MEDIUM 120
#define ENEMYSHOOTSPEED_MEDIUM 20
#define BASE_MEDIUM 0.4
#define ENEMYMOVESPEED_MEDIUM 6
#define MYTANK_MEDIUM 0.2

//hard
#define SPAWNSPEED_HARD 100
#define ENEMYSHOOTSPEED_HARD 15
#define BASE_HARD 0.5
#define ENEMYMOVESPEED_HARD 4
#define MYTANK_HARD 0.5

#define POWERS_PER_LEVEL 3
extern int power_indexes[];

typedef struct tank
{
    int x, y, dir, shoot_state, shoot_rate, shoot_speed, move_speed, move_state, move_rate, value, hit_points, stars, invulnerable, power_type, type, animation_counter;
    int AIDecisions [ AI_SPEED ], AIState;
    bool alive, player;
} Tank;

typedef struct bullet
{
    int x, y, dir, state, source;
    bool alive;
} Bullet;

typedef struct
{
    int type, x, y, state, time;
} Power;

typedef struct difficulty
{
    int spawn,shoot;
    int (*AI) ();
    int speed;
} Difficulty;

// types of tanks
enum { BASIC_TANK, FAST_TANK, POWER_TANK, ARMOR_TANK };

#define NUMBER_OF_POWERS 7
// types of power-ups
enum { NORMAL, BOMB, HELMET, SHOVEL, STAR, LIFE, TIMER };


int levelConfiguration[20];

// global variables
extern char characterMap[];

Tank tanks[MAX_SPRITES];
Tank player1, player2;
Bullet bullets[MAX_SPRITES];
extern int demo;
extern int totalSpawned, cntKilled, score;
extern int gameDifficulty;
extern const Difficulty confDiff[3];
extern char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE];
extern int mapUsed[MAP_SIZE][MAP_SIZE];
extern int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size, numberOfTanks;
extern Power power_up;
extern int CNT_KILLED[];
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
#include "ai.h"
#include "rsa.h"
#include "highscores.h"
#endif // GLOBAL_H_INCLUDED
