#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED
#define DEBUG 0


//start the gameloop
void start_game(char *, int);

//AI
void get_decision_easy(Tank *tank);
void get_decision_medium(Tank *tank);
void get_decision_hard(Tank *tank);

#endif // GAMELOOP_H_INCLUDED
