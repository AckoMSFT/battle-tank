#ifndef KLETVE_H_INCLUDED
#define KLETVE_H_INCLUDED
#define DEBUG 0

//initialize curses.h
void init_curses(void);

//initialize color pairs
void init_colors(void);

//print border with this coords
void print_border(int y1, int x1, int y2, int x2);

//print tank with this coords and direction
void print_tank(int dir, int y, int x);

//print specific fields
void print_empty(int y, int x);

void print_bullet(int y, int x);

void print_grass(int y, int x);

void print_water(int y, int x);

void print_brick(int y, int x);

void print_steel(int y, int x);

//print whole base
void print_base(int y, int x);

//finish with curses
void kill_curses(void);

//load map from file and draw a border
void load_map(char * input_file_name);

//print current state of the map and tanks and bullets and ALL
void print_map(void);

#endif // KLETVE_H_INCLUDED
