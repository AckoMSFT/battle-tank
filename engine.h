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
 *  @brief - Ispaljivanje metka iz tenka.
 *  @param *tank pokazivac na tenk
 */
void shoot( Tank *tank );

/**
 *  @brief - Azuriranje stanja svih tenkova i metkova.
 */
void update_states() ;

/**
 *  @brief - Kolizija metkova.
 */
int bullets_collision( Bullet bullet1, Bullet bullet2 );

/**
 *  @brief - Provera svih kolizija.
 */
void collision ( );

/**
 *  @brief - Da li metak moze da srusi dato polje?
 *  @param x, y koordinate polja
 *  @return true ili false.
 */
int bullet_can_collide(int x,int y);

/**
 *  @brief - Namestanje zida oko baze
 *  @param filedType tip zida
 */
void base_set(char fieldType);

/**
 *  @brief Stvaranje novog tenka
 *  @param x, y koordinate
 *  @param dir smer
 *  @param type tip
 *  @param speed brzina kretanja
 *  @param shootSpeed brzina pucanja
 */
void spawn_tank( int x, int y, int dir, int type, int speed, int shootSpeed );

#endif // ENGINE_H_INCLUDED
