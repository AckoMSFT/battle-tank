#include "global.h"

void find_space_tank(int *x, int *y){
    int i,j,empty,di,dj;
    int jPositions[3] = {0,MAP_SIZE/2 -1 , MAP_SIZE-3};
    int newRand = rand() % ENEMYSPAWNRANDOM;

    if (player1.x > 2 ) for(i=0;i<3;i++){
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


    for (i = 4; i < MAP_SIZE-2; i++)
        for (j = 0; j < MAP_SIZE-2; j++){

            empty = 1;
            for(di=0;di<3;di++) for(dj=0;dj<3;dj++){
                if (mapUsed[i+di][j+dj]) empty = 0;

            }

            if (empty && --newRand == 0){

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
            if (map[i][j] == EMPTY||map[i][j] == GRASS){
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
    int i;
    score = 0;
    gameDifficulty = difficulty;
    player1.hit_points = 3;
    player1.stars = 0;
    for (i = 1; i <= NUMBER_OF_LEVELS; i++)
    {
        bool gameOver = 1 - startLevel(i);
        if ( gameOver == true )
        {
            sound_end();
            kill_curses();
            puts("osvojio si");
            printf("%d\n",score);
            update_high_scores("al3ksandar",score);
            return;
        }
        else print_end_level_screen ( i );
    }
    kill_curses();
    puts("osvojio si");
    printf("%d\n",score);
    update_high_scores("al3ksandar",score);
    return;
}

bool startLevel(int level)
{
    print_start_level_screen(level);
    // give me current level
    char level_name[1 << 5], buffer[1 << 5];
    strcpy(level_name,"level");
    itoa(level, buffer, 10);
    strcat(level_name, buffer);
    strcat(level_name, ".map");
    load_map(level_name);


    int i,j,keyPressed,enemySpawn,x,y,enemyChoice,di,dj;
    const int SLEEP_TIME = 1000 / FRAMES_PER_SEC;

    gameOver = false;
    numberOfTanks = 0;
    for (i=0; i<MAX_SPRITES ; i++){
        tanks[i].alive = bullets[i].alive = 0;
    }
    enemySpawn = 0;
    myScore = 0;

    cntKilled = 0;

    // initialize player1
    player1.x = 36;
    player1.y = 12;
    player1.dir = UP;
    player1.alive = true;
    player1.move_state = 0;
    player1.shoot_state = 0;
    player1.invulnerable = FRAMES_PER_SEC * INVULNERABLE_SECS;
    player1.move_rate = 1;
    player1.move_speed = TANK_SPEED;
    player1.shoot_speed = SHOOT_SPEED;
    player1.shoot_rate = 1;
    player1.player = true;
    player1.power_type = NORMAL;
    //player1.stars = 2;
    totalSpawned = 0;

    power_up.x = 30;
    power_up.y = 10;
    power_up.type = NORMAL;
    power_up.state = 0;
    power_up.time = 0;

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
                spawn_tank(x,y,DOWN, levelConfiguration[totalSpawned],confDiff[gameDifficulty].speed,confDiff[gameDifficulty].shoot);
            }

        }
        hell:
        //now update the mapUsed
        update_mapUsed();

        //move the tanks !
        for ( i = 0; i < MAX_SPRITES; i++ )
        {
            if ( tanks[i].alive == false ) continue;
            if ( tanks[i].move_state < tanks[i].move_speed) continue;
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
                case KEY_F(6): return true;
            }
        }

        update_states();
        collision();

        print_map();

        for ( i = 0; i < MAP_SIZE; i++ )
            for ( j = 0; j < MAP_SIZE; j++ ) if ( map[i][j] == GRASS ) print_grass ( i + MAP_OFFSET_X, j + MAP_OFFSET_Y );
        refresh ( );
        for ( i = 0; i < MAP_SIZE; i++ )
            for ( j = 0; j < MAP_SIZE; j++ )
            {
                if ( map[i][j] == EXPLOSION_GRASS ) map[i][j] = GRASS;
                if ( map[i][j] == EXPLOSION ) map[i][j] = EMPTY;
            }

        print_power(&power_up);

        refresh ( );
        if ( cntKilled == TANKS_PER_LEVEL ) return true;
        if ( player1.hit_points <= 0 ) return false;
        print_indicators(totalSpawned, player1.hit_points, player1.stars, score);
        Sleep ( SLEEP_TIME );
    }
    return gameOver ^ 1;
}
