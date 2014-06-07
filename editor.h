#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

//this is a funciton for printing the editor
void print_editor();

//save editor to file mapFile.map
void save_editor(char * mapFile);

//change the type of a cursor
void change_cursor();

//add base to map at (x,y)
void create_base(int x, int y);

//add tank to map at (x,y)
void create_tank(int x, int y);

//erase tank
void erase_tank(int x, int y);

void create_cursor(int x, int y);

//move cursor
void move_right();

void move_left();

void move_up();

void move_down();

//initialize the editor with starting values and load it
void load_editor();

//function for drawing the right cursor
void draw_cursor();

//draw the right field at the right place
void draw_field(int x, int y);

//changing cursor size
void change_size();

//clear everything
void clear_editor();

//print the start wall
void print_wall(int a, int b);

//generate a random map
void map_generator(int n);

#endif // EDITOR_H_INCLUDED
