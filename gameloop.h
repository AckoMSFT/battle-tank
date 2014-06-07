#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED
#define DEBUG 0

//chose a level than call startgame
void choose_level();

//start the gameloop
void start_game();

//AI
void get_decision_easy(Tank *tank);
void get_decision_medium(Tank *tank);
void get_decision_hard(Tank *tank);

#endif // GAMELOOP_H_INCLUDED
