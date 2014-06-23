/**
 *  @file menu.h
 *  @brief - Definicija funkcije za crtanje menija.
 */
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/**
 *  @brief - Crtanje menija
 *  @param starty y koordinata gornjeg levog coska
 *  @param x x koordinata gornjeg levog coska
 *  @param number_of_entries broj stavki menija
 *  @param width sirina menija
 *  @param title naslov menija
 *  @param entries stavke menija
 *  @param idx indeks pocetne izabrana stavka u meniju
 *  @return indeks izabrane stavke u meniju
 */
int print_menu (int starty, int x, int number_of_entries, int width, char title[], char entries[][100], int idx);

#endif // MENU_H_INCLUDED
