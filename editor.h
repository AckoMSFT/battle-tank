/**
 *  @file editor.h
 *  @brief - Definicije funkcija za editor mape.
 */
#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

/**
 *  @brief - Iscrtavanje editora.
 */
void print_editor();

/**
 *  @brief - Iscrtavanje mape u datoteku.
 *  @param *mapFile ime datoteke
 */
void save_editor(char * mapFile);

/**
 *  @brief - Promena tipa kursora.
 */
void change_cursor();

/**
 *  @brief - Kreiranje baze na zadatim koordinatama.
 *  @param x, y koordinate
 */
void create_base(int x, int y);

/**
 *  @brief - Kreiranje tenka na zadatim koordinatama.
 *  @param x, y koordinate
 */
void create_tank(int x, int y);

/**
 *  @brief - Brisanje tenka sa zadatih koordinata.
 *  @param x, y koordinate
 */
void erase_tank(int x, int y);

/**
 *  @brief - Kreiranje kursora na zadatim koordinatama.
 *  @param x, y koordinate
 */
void create_cursor(int x, int y);

/**
 *  @brief - Pomeranje kursora u desno.
 */
void move_right();

/**
 *  @brief - Pomeranje kursora u levo.
 */
void move_left();

/**
 *  @brief - Pomeranje kursora na gore.
 */
void move_up();

/**
 *  @brief - Pomeranje kursora na dole.
 */
void move_down();

/**
 *  @brief - Inicijalizacija editora i ucitavanje nivoa.
 *  @param level nivo
 */
void load_editor(int level);

/**
 *  @brief - Iscrtavanje kursora
 */
void draw_cursor();

/**
 *  @brief - Iscrtavanje polja na zadatim koordinatama.
 *  @param x, y koordinate
 */
void draw_field(int x, int y);

/**
 *  @brief - Promena velicine kursora.
 */
void change_size();

/**
 *  @brief - Ciscenje editora.
 */
void clear_editor();

/**
 *  @brief - Ispisvanje proizvoljnog pravougaonog zida.
 *  @param a, b dimenzije
 */
void print_wall(int a, int b);

/**
 *  @brief - Generisanje proizvoljne mape.
 *  @param n broj zidova u mapi
 */
void map_generator(int n);

#endif // EDITOR_H_INCLUDED
