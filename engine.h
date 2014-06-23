/**
 *  @file engine.h
 *  @brief - Definicija funkcija za logiku igrice.
 */
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

/**
 *  @brief - Pomeranje tenka u zadatom smeru ukoliko je to moguce.
 *  @param *tank pokazivac na tenk
 *  @param direction smer
 */
void move_tank ( Tank *tank, int direction);

/**
 *  @brief - Pomeranje tenka na gore ukoliko je to moguce.
 *  @param *tank pokazivac na tenk
 */
void go_up( Tank *tank );

/**
 *  @brief - Pomeranje tenka na dole ukoliko je to moguce.
 *  @param *tank pokazivac na tenk
 */
void go_down( Tank *tank );

/**
 *  @brief - Pomeranje tenka u levo ukoliko je to moguce.
 *  @param *tank pokazivac na tenk
 */
void go_left( Tank *tank );

/**
 *  @brief - Pomeranje tenka u desno ukoliko je to moguce.
 *  @param *tank pokazivac na tenk
 */
void go_right( Tank *tank );

/**
 *  @brief - Pucanje
 *  @param *tank pokazivac na tenk
 *  @param origin poreklo metka
 */
void shoot( Tank *tank );
// Updating bullets states and moving them, and tank shooting states, and tank moving states
void update_states() ;
int bullets_collision( Bullet bullet1, Bullet bullet2 );
// Check for collisions of tanks and bullets, respectively bullets and bullets
void collision() ;
int bullet_can_collide(int x,int y);
void base_set(char fieldType);
//spawn a new tank
void spawn_tank( int x, int y, int dir, int lives, int, int );
#endif // ENGINE_H_INCLUDED
