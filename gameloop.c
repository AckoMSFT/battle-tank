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

    //update player_1
    for (dx = 0; dx < 3; dx++)
        for (dy = 0; dy < 3; dy++) mapUsed[player1.x + dx][player1.y + dy] = 1;

    //update tanks
    for (i = 0; i < MAX_SPRITES; i++) if (tanks[i].alive)
    {
        for (dx = 0; dx < 3; dx++)
            for (dy = 0; dy < 3; dy++) mapUsed[tanks[i].x + dx][tanks[i].y + dy] = 1;
    }

    //update bullets
    for (i = 0; i < MAX_SPRITES; i++) if (bullets[i].alive)
    {
        mapUsed[bullets[i].x][bullets[i].y] = 1;
    }
}



int get_decision_easy(Tank *tank){
    //0,1,2,3 are directions, 4 is shoot, and 5 is nothing
    return rand()%20;
}

int get_decision_medium(Tank *tank){
    return rand()%12;
}

int get_decision_hard(Tank *tank){
    return rand()%6;
}


void startGame(int difficulty)
{
    int i, stars = 0, score = 0;
    for (i = 1; i <= NUMBER_OF_LEVELS; i++)
    {
        score += startLevel(i, difficulty, &stars);
    }
}

int startLevel(int level, int difficulty, int *stars)
{
    char level_name[1 << 5], buffer[1 << 5];
    strcpy(level_name,"level");
    itoa(level, buffer, 10);
    strcat(level_name, buffer);
    strcat(level_name, ".map");

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
    gameOver = false;
    numberOfTanks = 0;
    for (i=0; i<MAX_SPRITES ; i++){
        tanks[i].alive = bullets[i].alive = 0;
    }
    enemySpawn = 0;
    myScore = 0;

    // initialize player1
    player1.hitPoints = 50000;
    player1.x = 36;
    player1.y = 12;
    player1.dir = UP;
    player1.alive = true;
    player1.moveState = 0;
    player1.shootState = 0;
    player1.invulnerable = false;
    player1.stars = stars;

    while(gameOver == false){

        /* Obtain current time as seconds elapsed since the Epoch. */
        current_time = time(NULL);
        /* Convert to local time format. */
        c_time_string = ctime(&current_time);



        //check if we should spawn an enemy tank
        enemySpawn++;
        if (enemySpawn == confDiff[ gameDifficulty ].spawn){
            enemySpawn = 0;
            //find me a spot for new enemy tank
            find_space_tank(&x,&y);

            //if
            if (x!=-1){
                if ( numberOfTanks < maxNumberOfTanks ) spawn_tank(x,y,DOWN, rand ( ) % 4 + 1);
            }

        }

        //now update the mapUsed
        update_mapUsed();

        //move the tanks !
        for ( i = 0; i < MAX_SPRITES; i++ ) if (tanks[i].alive) {
            enemyChoice = confDiff[gameDifficulty].AI(tanks + i);
            if (enemyChoice >=0 && enemyChoice <=3) move_tank(tanks+i, enemyChoice);
            else if (enemyChoice == 4) shoot(tanks+i, 0);
        }
        if (kbhit()){
            while(kbhit()){
                    keyPressed = read_input();

            }
            switch(keyPressed){

                case NEW_KEY_RIGHT:
                case NEW_KEY_LEFT:
                case NEW_KEY_UP:
                case NEW_KEY_DOWN:
                    move_tank(&player1, keyPressed - MIN_KEY);
                    break;
                case SPACE:
                    shoot(&player1, 1);
                    break;
            }
        }

        update_states();
        collision();

        print_map();
        Sleep(sleepTime);

        if ( player1.hitPoints <= 0 ) gameOver = true;
    }
    print_end_screen();
}
