/**
 *  @file sound.h
 *  @brief - Definicije funkcija za zvuk.
 */
#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

/**
 *  @brief - Pustanje zvukova.
 *  @param *sound ime .wav fajla
 */
void sound_play(char *sound);

/**
 *  @brief - Pustanje zvuka za kraj nivoa.
 */
void sound_level_end();

/**
 *  @brief - Pustanje zvuka za kraj igrice.
 */
void sound_end();

/**
 *  @brief - Pustanje zvuka za kraj nivoa.
 */
void sound_start_music();

/**
 *  @brief - Pustanje zvuka za eksploziju.
 */
void sound_explosion();

/**
 *  @brief - Pustanje zvuka za ispaljivanje metka.
 */
void sound_shot();

#endif // SOUND_H_INCLUDED
