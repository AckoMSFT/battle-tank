#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

void move_tank ( Tank *tank, int direction);
void go_up( Tank *tank );
void go_down( Tank *tank );
void go_left( Tank *tank );
void go_right( Tank *tank );
// Spawns new bullet after shoot command
void shoot( Tank *tank, int origin );
// Updating bullets states and moving them, and tank shooting states, and tank moving states
void update_states() ;
int bullets_collision( Bullet bullet1, Bullet bullet2 );
// Check for collisions of tanks and bullets, respectively bullets and bullets
void collision(int *, int *) ;

//spawn a new tank
void spawn_tank( int x, int y, int dir, int lives );
#endif // ENGINE_H_INCLUDED
