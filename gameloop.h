#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED
#define DEBUG 0

//find a first spot ehre a new tank can be put
void find_space_tank(int *x, int *y);

//update the mapused, so we can check collisions and find space and tank movement
void update_mapUsed(int usePowerUp);

//start the gameloop
void startGame(int);
int startLevel(int);

#endif // GAMELOOP_H_INCLUDED
