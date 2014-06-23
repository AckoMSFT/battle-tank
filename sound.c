/**
 *  @file sound.c
 *  @brief - Implementacije funkcija za zvuk.
 */
 #include "global.h"

void sound_play(char *sound){

#ifdef _WIN32
    PlaySound(sound,NULL, SND_ASYNC);
#endif
}

void sound_level_end(){
    sound_play("levelend.wav");
}

void sound_end(){
    sound_play("endgame.wav");

}

void sound_start_music(){
    sound_play("start_game.wav");

}

void sound_explosion(){
    sound_play("boom.wav");

}

void sound_shot(){
    sound_play("gun_shot.wav");
}
