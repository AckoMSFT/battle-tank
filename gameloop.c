#include "global.h"

void updateDecisions(Tank *tank,float baseRandom, float mytankRandom){

    int x = tank->x, y = tank->y,i,dx,dy,di,dj, currX, currY, empty, popX, popY,dir, fromX, fromY;
    float newRand = (float)rand()/(float)RAND_MAX;
    int mapMove[MAP_SIZE][MAP_SIZE], mapMoveLast[MAP_SIZE][MAP_SIZE];
    char mapAI[MAP_SIZE][MAP_SIZE];
    queue matrixQueue;
    //what map to use ??
    for(di=0; di<MAP_SIZE; di++) for (dj =0; dj<MAP_SIZE; dj++) mapAI[di][dj] = map[di][dj];

    //update player_1 to mapAI
    for (dx = 0; dx < 3; dx++)
        for (dy = 0; dy < 3; dy++) mapAI[player1.x + dx][player1.y + dy] = 'T';

    //update tanks to mapAI
    for (i = 0; i < MAX_SPRITES; i++) if (tanks[i].alive)
    {
        for (dx = 0; dx < 3; dx++)
            for (dy = 0; dy < 3; dy++) mapAI[tanks[i].x + dx][tanks[i].y + dy] = 'T';
    }

    //set empty for this tank
    for (dx = 0; dx < 3; dx++)
        for (dy = 0; dy < 3; dy++) mapAI[tank->x + dx][tank->y + dy] = EMPTY;



    matrixQueue.front = matrixQueue.end = 0;
    memset(mapMove,0,sizeof(mapMove));
    memset(mapMoveLast,0,sizeof(mapMove));


    //go towards base
    if (newRand < baseRandom + mytankRandom){

        if (newRand < baseRandom){
            //go toward base
            fromX = base_x;
            fromY = base_y;

        }
        else{
            //go toward ME
            fromX = player1.x+1;
            fromY = player1.y+1;

        }

        //generate mapShoot and init for mapMove (set ones from the spot that can shoot)
        for (dx = -1; dx < 2; dx++)
            for (dy = -1; dy < 2; dy++){
                if ( (dx+dy)%2 == 0) continue;

                currX = fromX;
                currY = fromY;

                empty=1;
                while(empty && currX < MAP_SIZE -2 && currX >= 0 && currY < MAP_SIZE -2 && currY >= 0){

                    for(di=0;di<3;di++) for(dj=0;dj<3;dj++){
                        if (mapAI[ currX + di ][ currY + dj ] != EMPTY ) empty = 0;
                    }

                    if (empty){
                        mapMove[currX][currY] = 1;
                        queuePush(&matrixQueue, currX*MAP_SIZE + currY);
                    }


                    empty =1;
                    for(di=0;di<3;di++) for(dj=0;dj<3;dj++){
                        if (mapAI[ currX + di ][ currY + dj ] == STEEL ) empty = 0;
                    }

                    currX += dx;
                    currY += dy;

                }


            }

            //now find path to player
            while(! queueEmpty( &matrixQueue )){

                //this is some retarded data representation in a queue (two ints in a int)
                popX = queuePop(&matrixQueue);
                popY = popX % MAP_SIZE;
                popX /= MAP_SIZE;

                if (popX ==0 && popY ==0){
                    popX =0 ;

                }

                for (dx = -1; dx < 2; dx++)
                    for (dy = -1; dy < 2; dy++){
                        if ( (dx+dy)%2 == 0) continue;

                        currX = popX + dx;
                        currY = popY + dy;

                        //off the map
                        if (currX >MAP_SIZE -2 || currY > MAP_SIZE -2 || currX < 0 || currY < 0) continue;

                        empty =1;
                        for(di=0;di<3;di++) for(dj=0;dj<3;dj++){
                            if (mapAI[ currX + di ][ currY + dj ] != EMPTY ) empty = 0;
                        }

                        if (empty && ( mapMove[ currX ][ currY ]==0 || mapMove[ currX ][ currY ] > mapMove[ popX ][ popY ] + 1) ){
                            mapMove[ currX ][ currY ] = mapMove[ popX ][ popY ] + 1;
                            queuePush(&matrixQueue, currX*MAP_SIZE + currY);

                            switch (dx){

                            case 0:
                                switch(dy){

                                case -1:
                                    mapMoveLast[ currX ][ currY ] = RIGHT;
                                    break;
                                case 1:
                                    mapMoveLast[ currX ][ currY ] = LEFT;
                                    break;

                                }
                                break;
                            case -1:
                                mapMoveLast[ currX ][ currY ] = DOWN;
                                break;

                            case 1:
                                mapMoveLast[ currX ][ currY ] = UP;
                                break;
                            }
                        }

                }

            }

            currX = tank->x;
            currY = tank->y;


            //you can go to the base
            if (mapMove[ currX ][ currY ]){

                i=AI_SPEED;

                while(i--){

                    if (mapMove[ currX ][ currY ] == 1 ){

                        if (currX == fromX){
                            if (currY > base_y){
                                dir = LEFT;
                            }
                            else{
                                dir = RIGHT;
                            }
                        }
                        else{
                            if (currX > fromY){
                                dir = UP;
                            }
                            else{
                                dir = DOWN;
                            }

                        }

                        //now check if the last decision was exactly this direction
                        if ( i== AI_SPEED-1 ){
                            if (tank->dir != dir){

                                tank->AIDecisions[ i-- ] = dir;

                            }

                        }
                        else{
                            if (tank->AIDecisions[ i+1 ] != dir){

                                tank->AIDecisions[ i-- ] = dir;
                            }

                        }

                        //now lets shoot !!!

                        while(i >=0 ) tank->AIDecisions[ i-- ] = 4;
                        return ;

                    }
                    else {
                        tank->AIDecisions[ i ] = mapMoveLast[ currX ][ currY ];
                        switch(mapMoveLast[currX][currY]){
                        case DOWN:
                            currX++;
                            break;
                        case UP:
                            currX--;
                            break;
                        case RIGHT:
                            currY++;
                            break;
                        case LEFT:
                            currY--;
                            break;
                        }
                    }


                }

                return ;
            }

    }

    //just do it random
    for( i=0; i<AI_SPEED; i++ ){
        tank->AIDecisions[i] = rand()%6;

    }


}

int get_decision_easy(Tank *tank){
    if (--(tank->AIState) < 0){

        updateDecisions(tank, BASE_EASY,MYTANK_EASY);

        tank->AIState = AI_SPEED-1;
    }

    return tank->AIDecisions[ tank->AIState ];
}

int get_decision_medium(Tank *tank){
    if (--(tank->AIState) < 0){

        updateDecisions(tank, BASE_MEDIUM,MYTANK_MEDIUM);

        tank->AIState = AI_SPEED-1;
    }

    return tank->AIDecisions[ tank->AIState ];
}

int get_decision_hard(Tank *tank){
    if (--(tank->AIState) < 0){

        updateDecisions(tank, BASE_HARD,MYTANK_HARD);

        tank->AIState = AI_SPEED-1;
    }

    return tank->AIDecisions[ tank->AIState ];
}


void find_space_tank(int *x, int *y){
    int i,j,empty,di,dj;
    int jPositions[3] = {0,MAP_SIZE/2 -1 , MAP_SIZE-3};

    for(i=0;i<3;i++){
        j=jPositions[(i + totalSpawned) %3];
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
            sound_end();
            kill_curses();
            puts("osvojio si");
            printf("%d\n",score);
            update_high_scores("al3ksandar",score);
            return;
        }
    }
    kill_curses();
    puts("osvojio si");
    printf("%d\n",score);
    update_high_scores("al3ksandar",score);
    return;
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
            if ( tanks[i].move_state < TANK_SPEED) continue;
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

        if ( player1.invulnerable > 0 ) if ( player1.invulnerable % 5 == 3 ) attron ( A_BLINK );
        print_tank(player1.dir, player1.x + 1, player1.y + 1);
        if ( player1.invulnerable > 0 ) if ( player1.invulnerable % 5 == 3 ) attroff ( A_BLINK );
        if ( player1.invulnerable > 0 ) player1.invulnerable--;
        refresh();

        powerUP.state = ( powerUP.state + 1 ) % 5;
        print_power_up(powerUP);
        if ( cntKilled == TANKS_PER_LEVEL ) return true;
        if ( player1.hit_points <= 0 ) return false;

        print_indicators(totalSpawned, player1.hit_points, * stars, * score);
        Sleep(sleepTime);
    }
    return gameOver ^ 1;
}
