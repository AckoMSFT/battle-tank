#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
void updateDecisions(Tank *tank,float baseRandom, float mytankRandom, int chaseMeX, int chaseMeY, int aiSpeed, int aiParam1 ,int aiParam2, int dontShoot);
int get_decision_easy(Tank *tank);
int get_decision_medium(Tank *tank);
int get_decision_hard(Tank *tank);
int get_decision_demo();
#endif AI_H_INCLUDED
