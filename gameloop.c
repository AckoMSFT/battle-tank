#include "global.h"



void updateDecisions(){



}

int get_decision_easy(Tank *tank){
//    if (AIState++ == AI_SPEED){
//
//        updateDecisions();
//
//        AIState=0;
//    }
//
//    return AIDecisions[AIState];

    return rand()%20;
}

int get_decision_medium(Tank *tank){
    return rand()%12;
}

int get_decision_hard(Tank *tank){
    return rand()%6;
}


void find_space_tank(int *x, int *y){
    int i,j,empty,di,dj;
    int jPositions[2] = {0,MAP_SIZE/2 -1 , MAP_SIZE-2};

    for(i=0;i<3;i++){
        j=jPositions[i];
        empty = 1;
        for(di=0;di<3;di++) for(dj=0;dj<3;dj++){
            if (mapUsed[di][j+dj]) empty = 0;

        }

        if (empty){
            *x= 0;
            *y=j;
            return;
        }
    }

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



void update_status(int lives, int score, int stars)
{
    move(10,50);
    printw("%d %d %d\n", lives, score, stars);
}

void startGame(int difficulty)
{
    int i, stars = 0, score = 0;
    gameDifficulty = difficulty;
    player1.hit_points = 3;
    for (i = 1; i <= NUMBER_OF_LEVELS; i++)
    {
        bool gameOver = 1 - startLevel(i, &stars, &score);
        if ( gameOver == true )
        {
            kill_curses();
            puts("osvojio si");
            printf("%d\n",score);
            update_high_scores("al3ksandar",score);
            exit(0);
        }
    }
    kill_curses();
    puts("osvojio si");
    printf("%d\n",score);
    update_high_scores("al3ksandar",score);
    exit(0);
}

bool startLevel(int level, int *stars, int *score)
{
    Power powerUP;
    // give me current level
    char level_name[1 << 5], buffer[1 << 5];
    strcpy(level_name,"level");
    itoa(level, buffer, 10);
    strcat(level_name, buffer);
    strcat(level_name, ".map");
    load_map(level_name);
    sound_start_music();


    int i,keyPressed,enemySpawn,x,y,enemyChoice,di,dj, cntKilled = 0;
    const int sleepTime = 1000 / FRAMES_PER_SEC;

    gameOver = false;
    numberOfTanks = 0;
    for (i=0; i<MAX_SPRITES ; i++){
        tanks[i].alive = bullets[i].alive = 0;
    }
    enemySpawn = 0;
    myScore = 0;

    // initialize player1
    player1.x = 36;
    player1.y = 12;
    player1.dir = UP;
    player1.alive = true;
    player1.move_state = 0;
    player1.shoot_state = 0;
    player1.invulnerable = FRAMES_PER_SEC * INVULNERABLE_SECS;
    player1.stars = stars;
    player1.move_rate = 1;
    player1.shoot_rate = 1;
    totalSpawned = 0;

    powerUP.x = 50;
    powerUP.y = 50;
    powerUP.type = BOMB;
    powerUP.state = 0;
    while(gameOver == false)
    {
        enemySpawn++;
        if ( enemySpawn == confDiff[gameDifficulty].spawn )
        {
            if ( numberOfTanks == MAX_NUMBER_OF_TANKS || totalSpawned == TANKS_PER_LEVEL )
            {
                enemySpawn--;
                goto hell;
            }
            enemySpawn = 0;
            //find me a spot for new enemy tank
            find_space_tank(&x,&y);

            //if
            if (x!=-1){
                spawn_tank(x,y,DOWN, levelConfiguration[totalSpawned]);
            }

        }
        hell:
        //now update the mapUsed
        update_mapUsed();

        //move the tanks !
        for ( i = 0; i < MAX_SPRITES; i++ )
        {
            if ( tanks[i].alive == false ) continue;
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
        collision(&cntKilled, score);

        print_map();
        update_status(player1.hit_points, *score, *stars);

        if ( player1.invulnerable > 0 ) if ( player1.invulnerable % 5 == 3 ) attron ( A_BLINK );
        print_tank(player1.dir, player1.x + 1, player1.y + 1);
        if ( player1.invulnerable > 0 ) if ( player1.invulnerable % 5 == 3 ) attroff ( A_BLINK );
        if ( player1.invulnerable > 0 ) player1.invulnerable--;
        refresh();

        powerUP.state = ( powerUP.state + 1 ) % 5;
        print_power_up(powerUP);
        if ( cntKilled == TANKS_PER_LEVEL ) return true;
        if ( player1.hit_points <= 0 ) return false;

        print_tank_indicators(totalSpawned);
        Sleep(sleepTime);
    }
    return gameOver ^ 1;
}
