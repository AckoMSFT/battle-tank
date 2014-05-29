#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#ifdef _WIN32
#define _WIN32_WINNT 0x0600
#include <windows.h>
#endif

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define    UP 0
#define  DOWN 1
#define  LEFT 2
#define RIGHT 3
#define SPACE ' '

#define MAP_OFFSET_X 1
#define MAP_OFFSET_Y 1
#define MAP_SIZE 41

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

typedef struct
{
    int x, y, dir,val;
}Tank;
Tank tanks[ MAXSPRITES ];

Tank myTank = {36,13,0,1};

typedef struct
{
    int x, y, dir, state,val;
}Bullet;
Bullet bullets[ MAXSPRITES ];

int gameOver;

char map[MAP_SIZE+2][MAP_SIZE+2], editor[MAP_SIZE][MAP_SIZE], character_map[] = { '.', 'B', 'S', 'W', 'X', 'T' }, level_name[] = "Level0x01.txt"; // level name currently not used, and it shouldnt be used.
int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;
#endif // GLOBAL_H_INCLUDED
