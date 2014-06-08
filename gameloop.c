#include "global.h"


void find_space_tank(int *x, int *y){
    int i,j,empty,di,dj;
    for (i = 0; i < MAP_SIZE-2; i++)
        for (j = 0; j < MAP_SIZE-2; j++){

            empty = 1;
            for(di=0;di<3;di++) for(dj=0;dj<3;dj++){
                if (mapUsed[i+di][j+dj]) empty = 0;

            }

            if (empty){
                *x= i;
                *y=j;
                return;
            }

        }
    x = -1;
    return;
}



void update_mapUsed(){
    int i,j,dx,dy;

    //update from map
    for (i = 0; i < MAP_SIZE; i++)
        for (j = 0; j < MAP_SIZE; j++)
        {
            if (map[i][j] == EMPTY){
                mapUsed[i][j] = 0;
            }
            else{
                mapUsed[i][j] = 1;
            }
        }

    //update myTank
    for (dx = 0; dx < 3; dx++)
        for (dy = 0; dy < 3; dy++) mapUsed[myTank.x + dx][myTank.y + dy] = 1;

    //update tanks
    for (i = 0; i < MAXSPRITES; i++) if (tanks[i].val)
    {
        for (dx = 0; dx < 3; dx++)
            for (dy = 0; dy < 3; dy++) mapUsed[tanks[i].x + dx][tanks[i].y + dy] = 1;
    }

    //update bullets
    for (i = 0; i < MAXSPRITES; i++) if (bullets[i].val)
    {
        mapUsed[bullets[i].x][bullets[i].y] = 1;
    }
}



int get_decision_easy(Tank *tank){
    //0,1,2,3 are directions, 4 is shoot, and 5 is nothing
    return rand()%6;
}

int get_decision_medium(Tank *tank){
    return rand()%6;
}

int get_decision_hard(Tank *tank){
    return rand()%6;
}



void start_game(char * level_name, int difficulty){
    load_map(level_name);
    gameDifficulty = difficulty;
    time_t current_time;
    char* c_time_string;
    /* Obtain current time as seconds elapsed since the Epoch. */
    current_time = time(NULL);
    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    int i,keyPressed,enemySpawn,x,y,enemyChoice,di,dj;
    const int sleepTime = 1000 / FRAMES_PER_SEC;

    //init some elements
    gameOver = 0;
    for (i=0; i<MAXSPRITES ; i++){
        tanks[i].val = bullets[i].val = 0;
    }
    enemySpawn = 0;


    while(!gameOver){

        /* Obtain current time as seconds elapsed since the Epoch. */
        current_time = time(NULL);
        /* Convert to local time format. */
        c_time_string = ctime(&current_time);



        //check if we should spawn an enemy tank
        enemySpawn++;
        if (DEBUG) {
                move(18,50);
                printw("enemyspawn %d",enemySpawn);
        }
        if (enemySpawn == confDiff[ gameDifficulty ].spawn){
            enemySpawn = 0;
            //find me a spot for new enemy tank
            find_space_tank(&x,&y);

            //if valid
            if (x!=-1){
                spawn_tank(x,y,DOWN);
                if (DEBUG) {
                        move(19,50);
                        printw("spawned tank at %d %d",x,y);
                }

            }

        }

        //now update the mapUsed
        update_mapUsed();

        //move the tanks !
        for ( i = 0; i < MAXSPRITES; i++ ) if (tanks[i].val) {
            enemyChoice = confDiff[gameDifficulty].AI(tanks + i);
            if (enemyChoice >=0 && enemyChoice <=3) move_tank(tanks+i, enemyChoice);
            else if (enemyChoice == 4) shoot(tanks+i);
        }

        if (DEBUG) {
            move(2,50);
            printw("%s",c_time_string);
        }
        //if keyboard is hit update the main tank position or shoot
        if (kbhit()){

            //get the last pressed key
            while(kbhit()){
                    keyPressed = read_input();

            }
            if (DEBUG) {
                    move(4,50);
                    printw("blah pressed %d %d",keyPressed, NEW_KEY_RIGHT);
                    refresh();
            }

            switch(keyPressed){

                case NEW_KEY_RIGHT:
                case NEW_KEY_LEFT:
                case NEW_KEY_UP:
                case NEW_KEY_DOWN:
                    if (DEBUG) printw("im here ! %d",keyPressed - MIN_KEY);
                    move_tank(&myTank, keyPressed - MIN_KEY);
                    break;
                case SPACE:
                    shoot(&myTank);
                    break;
            }

            if (DEBUG) {
                move(10,50);
                printw("pressed %d, but keyright is %d, and keyright == pressed %d",keyPressed,KEY_RIGHT,keyPressed==KEY_RIGHT);
                refresh();
            }
        }

        update_states();
        collision();

        print_map();
        Sleep(sleepTime);

    }

}
