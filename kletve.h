/**
 *  @file kletve.h
 *  @brief - Definicije funkcija za crtanje.
 */
#ifndef KLETVE_H_INCLUDED
#define KLETVE_H_INCLUDED

/**
 *  @brief - Inicijalizacija stvari potrebnih za rad biblioteke ncurses.
 */
void init_curses ( void );

/**
 *  @brief - Inicijalizacija parova (foreground, background) boja.
 */
void init_colors ( void );

/**
 *  @brief - Iscrtavanje okvira sa koordinatama gornjeg levog coska (y1, x1) i donjeg desnog coska (y2, x2).
 */
void print_border ( int y1, int x1, int y2, int x2 );

/**
 *  @brief - Iscrtavanje igracevog tenka.
 *  @param *this pokazivac na tenk
 */
void print_player_tank ( Tank * this );

/**
 *  @brief - Iscrtavanje armor tenka.
 *  @param dir smer
 *  @param y, x koordinate
 *  @param hit_points zivotni bodovi
 */
void print_armor_tank ( int dir, int y, int x, int hit_points );

/**
 *  @brief - Iscrtavanje fast tenka.
 *  @param dir smer
 *  @param y, x koordinate
 */
void print_fast_tank ( int dir, int y, int x );

/**
 *  @brief - Iscrtavanje power tenka.
 *  @param dir smer
 *  @param y, x koordinate
 */
void print_power_tank ( int dir, int y, int x );

/**
 *  @brief - Iscrtavanje basic tenka.
 *  @param dir smer
 *  @param y, x koordinate
 */
void print_basic_tank ( int dir, int y, int x );

/**
 *  @brief - Iscrtavanje tenka.
 *  @param *this pokazivac na tenk
 */
void print_tank ( Tank * this );

/**
 *  @brief - Iscrtavanje praznog polja.
 *  @param y, x koordinate
 */
void print_empty ( int y, int x );

/**
 *  @brief - Iscrtavanje metka.
 *  @param y, x koordinate
 *  @param source izvor
 */
void print_bullet ( int y, int x, int source );

/**
 *  @brief - Iscrtavanje trave.
 *  @param y, x koordinate
 */
void print_grass ( int y, int x );

/**
 *  @brief - Iscrtavanje vode.
 *  @param y, x koordinate
 */
void print_water ( int y, int x );

/**
 *  @brief - Iscrtavanje cigle.
 *  @param y, x koordinate
 */
void print_brick ( int y, int x );

/**
 *  @brief - Iscrtavanje celika.
 *  @param y, x koordinate
 */
void print_steel ( int y, int x );

/**
 *  @brief - Iscrtavanje eksplozije.
 *  @param y, x koordinate
 */
void print_explosion ( int y, int x );

/**
 *  @brief - Iscrtavanje proizvoljnog polja.
 *  @param y, x koordinate
 *  @param type tip polja
 */
void print_field ( int y, int x, int type );

/**
 *  @brief - Iscrtavanje bombe.
 *  @param y, x koordinate
 */
void print_bomb ( int y, int x );

/**
 *  @brief - Iscrtavanje slema.
 *  @param y, x koordinate
 */
void print_helmet ( int y, int x );

/**
 *  @brief - Iscrtavanje zvezde.
 *  @param y, x koordinate
 */
void print_star ( int y, int x );

/**
 *  @brief - Iscrtavanje lopate.
 *  @param y, x koordinate
 */
void print_shovel ( int y, int x );

/**
 *  @brief - Iscrtavanje tajmera.
 *  @param y, x koordinate
 */
void print_timer ( int y, int x );

/**
 *  @brief - Iscrtavanje zivota.
 *  @param y, x koordinate
 */
void print_life ( int y, int x );

/**
 *  @brief - Iscrtavanje power up-a.
 *  @param *this pokazivac na power up
 */
void print_power ( Power * this );

/**
 *  @brief - Iscrtavanje baze.
 *  @param y, x koordinate
 */
void print_base ( int y, int x );

/**
 *  @brief - Ucitvanje mape iz datoteke.
 *  @param *input_file_name ime datoteke u kojoj se nalzi mapa
 */
void load_map ( char * input_file_name );

/**
 *  @brief - Iscrtvanje mape.
 */
void print_map ( void );

/**
 *  @brief - Iscrtvanje ekrana na pocetku nivoa.
 *  @param level nivo
 */
void print_start_level_screen ( int level );

/**
 *  @brief - Iscrtvanje ekrana na kraju nivoa.
 *  @param level nivo
 */
void print_end_level_screen ( int level );

/**
 *  @brief - Brisanje tenka sa ekrana.
 *  @param y, x koordinate
 */
void print_empty_tank ( int y, int x );

/**
 *  @brief - Iscrtvanje cifre.
 *  @param y, x koordinate
 *  @param digit cifra
 */
void print_digit ( int y, int x, int digit );

/**
 *  @brief - Iscrtvanje indikatora sa desne strane u toku nivoa.
 *  @param totalSpawned broj tenkova koji se do sada stvorio
 *  @param stars broj zvezda koji je tenk pokupio
 *  @param score trenutni skor igraca
 */
void print_indicators ( int totalSpawned, int lives, int stars, int score );

/**
 *  @brief - Prestanak sa radom biblioteke ncurses.
 */
void kill_curses ( void );
#endif // KLETVE_H_INCLUDED
