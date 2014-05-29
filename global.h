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
#define MAP_SIZE 39

//map tile types
#define  TANK 'T'
#define  BASE 'X'
#define WATER 'W'
#define GRASS 'G'
#define EMPTY '.'
#define STEEL 'S'
#define BRICK 'B'

//game config options
#define DEBUG 0
#define FRAMES_PER_SEC 30

typedef struct
{
    int x, y, dir;
}Tank;
Tank *tank[ 20 ] = { 0 };

Tank myTank = {10,10,0};

typedef struct
{
    int x, y, dir;
}Bullet;
Bullet *bullets[ 20 ] = { 0 };

int gameOver;

char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE], character_map[] = { '.', 'B', 'S', 'W', 'X', 'T' }, level_name[] = "Level0x01.txt"; // level name currently not used, and it shouldnt be used.
int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;
#endif // GLOBAL_H_INCLUDED
