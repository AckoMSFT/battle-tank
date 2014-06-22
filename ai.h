#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
void updateDecisions(Tank *tank,float baseRandom, float mytankRandom);
int get_decision_easy(Tank *tank);
int get_decision_medium(Tank *tank);
int get_decision_hard(Tank *tank);
#endif AI_H_INCLUDED
