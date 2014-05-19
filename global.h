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

#define MAP_OFFSET_X 1
#define MAP_OFFSET_Y 1
#define MAP_SIZE 39

#define  TANK 'T'
#define  BASE 'X'
#define WATER 'W'
#define GRASS 'G'
#define EMPTY '.'
#define STEEL 'S'
#define BRICK 'B'

char map[MAP_SIZE][MAP_SIZE], editor[MAP_SIZE][MAP_SIZE], character_map[] = { '.', 'B', 'S', 'W', 'X', 'T' }, level_name[] = "Level0x01.txt";
int tank_x, tank_y, base_x, base_y, editor_cursor_x, editor_cursor_y, editor_cursor_id, editor_cursor_size;

#endif // GLOBAL_H_INCLUDED
