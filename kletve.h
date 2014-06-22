#ifndef KLETVE_H_INCLUDED
#define KLETVE_H_INCLUDED
void init_curses(void);
void init_colors(void);
void print_border(int y1, int x1, int y2, int x2);
void print_tank(Tank * this);
void print_enemy_tank(int dir, int y, int x, int lives);
void print_empty(int y, int x);
void print_bullet(int y, int x);
void print_grass(int y, int x);
void print_water(int y, int x);
void print_brick(int y, int x);
void print_steel(int y, int x);
void print_bomb(int y, int x);
void print_hlemet ( int y, int x );
void print_star(int y, int x);
void print_shovel(int y, int x);
void print_base(int y, int x);
void kill_curses(void);
void load_map(char * input_file_name);
void print_map(void);
void print_end_screen(void);
#endif // KLETVE_H_INCLUDED
