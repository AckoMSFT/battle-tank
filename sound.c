#include "global.h"

void sound_end(){
    PlaySound("endgame.wav", NULL, SND_ASYNC);

}

void sound_start_music(){
    PlaySound("start_game.wav", NULL, SND_ASYNC);

}

void sound_explosion(){
    PlaySound("boom.wav", NULL, SND_ASYNC);

}

void sound_shot(){
    PlaySound("gun_shot.wav", NULL, SND_ASYNC);
}
