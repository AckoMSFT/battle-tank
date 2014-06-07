#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#ifdef _WIN32
#define _WIN32_WINNT 0x0600
#include <windows.h>
#endif

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define  DOWN 0
#define    UP 1
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
#define FRAME 'F'

//game config options
#define DEBUG 0
#define MAXSPRITES 20
#define FRAMES_PER_SEC 30
#define BULLETSPEED 3
#define SHOOTSPEED 15
#define TANKSPEED 15

typedef struct
{
    int x, y, dir,val, shootState,moveState;
}Tank;



typedef struct
{
    int x, y, dir, state,val;
}Bullet;

extern Tank tanks[ MAXSPRITES ];
extern Tank myTank;
extern Bullet bullets[ MAXSPRITES ];
extern int gameOver;
extern char map[MAP_SIZE+2][MAP_SIZE+2], editor[MAP_SIZE][MAP_SIZE], character_map[];
extern int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;
#endif // GLOBAL_H_INCLUDED
