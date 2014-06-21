#include "global.h"

// moves the tank
void move_tank ( Tank *tank, int direction){

    //if this tank moved TANKSPEED earlier, just ignore. else, set movestate to 0
    if (tank->moveState < TANK_SPEED) return;

    tank->moveState = 0;

    switch(direction){
    case LEFT:
        go_left(tank);
        break;
    case RIGHT:
        go_right(tank);
        break;
    case UP:
        go_up(tank);
        break;
    case DOWN:
        go_down(tank);
        break;
    }
}

void go_up( Tank *tank )
{
    int up = tank->x - 1;
    int x = tank->x, y = tank->y;
    tank->dir = UP;
    if ( (up >=0 ) && ( mapUsed[ up ][ y ] == 0 ) && ( mapUsed[ up ][ y + 1 ] == 0 ) && ( mapUsed[ up ][ y + 2 ] == 0 ) ) tank->x = up;
}

void go_down( Tank *tank )
{
    int down = tank->x + 3;
    int x = tank->x, y = tank->y;
    tank->dir = DOWN;
    if ( (down < MAP_SIZE ) && ( mapUsed[ down ][ y ] == 0 ) && ( mapUsed[ down ][ y + 1 ] == 0 ) && ( mapUsed[ down ][ y + 2 ] == 0 ) ) tank->x = down - 2;
}
void go_left( Tank *tank )
{
    int left = tank->y - 1;
    int x = tank->x, y = tank->y;
    tank->dir = LEFT;
    if ( (left >= 0 ) && ( mapUsed[ x ][ left ] == 0 ) && ( mapUsed[ x + 1 ][ left ] == 0 ) && ( mapUsed[ x + 2 ][ left ] == 0 ) ) tank->y = left;
}
void go_right( Tank *tank )
{
    int right = tank->y + 3;
    int x = tank->x, y = tank->y;
    tank->dir = RIGHT;
    if ( (right < MAP_SIZE ) && ( mapUsed[ x ][ right ] == 0 ) && ( mapUsed[ x + 1 ][ right ] == 0 ) && ( mapUsed[ x + 2 ][ right ] == 0 ) ) tank->y = right - 2;
}
void shoot( Tank *tank, int origin ) // Spawns new bullet after shoot command
{
    int i, x, y;


    //if this tank shoot SHOOTSPEED earlier, just ignore.
    if (tank->shootState < SHOOT_SPEED) return;

    //get x, y of a new bullet
    switch( tank->dir ){
    case ( UP ):
        x = tank->x - 1;
        y = tank->y + 1;
        break;
    case ( RIGHT ):
        x = tank->x + 1;
        y = tank->y + 3;
        break;
    case ( LEFT ):
        x = tank->x + 1;
        y = tank->y - 1;
        break;
    case ( DOWN ):
        x = tank->x + 3;
        y = tank->y + 1;
        break;
    }

    //spawn a new bullet at first free spot in bullets array
    for ( i = 0; i < MAX_SPRITES; i++ )
        if ( bullets[i].alive == false )
        {
            bullets[i].alive = true;
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].dir = tank->dir;
            bullets[i].state = 0;
            bullets[i].source = origin;

            //tank shouldnt fire to fast, and also shouldnt kill itself by moving to bullet position by accident :D
            tank->shootState = 0;
            tank->moveState = 0;
            break;
        }
}

void update_states() // Updating bullets states and moving them, and tank shooting states, and tank moving states
{
    int i;

    //update the tanks shoot state and movestate
    for(i=0; i < MAX_SPRITES ; i++){
        if (tanks[ i ].alive == true){

            if (tanks[ i ].moveState < TANK_SPEED){
                tanks[ i ].moveState++;
            }

            if (tanks[ i ].shootState < SHOOT_SPEED){
                tanks[ i ].shootState++;
            }

        }


    }
    //also for player_1
    if (player1.shootState < SHOOT_SPEED) player1.shootState++;
    if (player1.moveState < TANK_SPEED) player1.moveState++;


    for ( i = 0; i < MAX_SPRITES; i++ )
        if ( bullets[ i ].alive == true )
        {
            bullets[ i ].state++;
            if ( bullets[ i ].state == BULLET_SPEED )
            {
                switch ( bullets[ i ].dir )
                {
                    case ( UP ):
                        bullets[ i ].x--;
                        break;
                    case ( DOWN ):
                        bullets[ i ].x++;
                        break;
                    case ( LEFT ):
                        bullets[ i ].y--;
                        break;
                    case ( RIGHT ):
                        bullets[ i ].y++;
                        break;
                }
                bullets[ i ].state = 0;
            }
        }
}

void collision(int * cntKilled, int * score) // Check for collisions of tanks and bullets, respectively bullets and bullets
{
    int i, j, di, dj;
    //check for tank-bullet colisions
    for (i = 0; i < MAX_SPRITES; i++)
        for (j = 0; j < MAX_SPRITES; j++) if (tanks[i].alive && bullets[j].alive )
        {
            if ( bullets[j].source == 0 ) continue;
            bool hit = false;
            for( di = 0; di < 3; di++) for( dj = 0; dj < 3; dj++){

                if ( ( tanks[ i ].x + di == bullets[ j ].x ) && ( tanks[ i ].y + dj == bullets[ j ].y ) ) hit = true;
            }
            if ( hit )
            {
                tanks[i].hitPoints--;
                bullets[ j ].alive = false;
                if (tanks[i].hitPoints <= 0)
                {
                    tanks[i].alive = false;
                    * score += tanks[i].value;
                    ( * cntKilled )++;
                    numberOfTanks--;
                }
            }
    }

    //check for bullet-bullet colisions
    for ( i = 0; i < MAX_SPRITES; i++ )
        for ( j = 0; j < MAX_SPRITES; j++ ) if (bullets[ i ].alive && bullets[ j ].alive)
        if ( ( i != j ) && ( bullets[ i ].x == bullets[ j ].x ) && ( bullets[ i ].y == bullets[ j ].y ) )
        {
            if (bullets[i].source == 0 && bullets[j].source == 0) continue;
            if (bullets[i].source > 0 && bullets[j].source > 0) continue;
            bullets[ i ].alive = 0;
            bullets[ j ].alive = 0;
        }

    //check for bullet-frame collisions
    for ( i = 0; i < MAX_SPRITES; i++ ) if (bullets[ i ].alive)
        if ( bullets[ i ].x < 0 || bullets[ i ].y < 0 || bullets[ i ].x >= MAP_SIZE || bullets[ i ].y >= MAP_SIZE  )
        {
            bullets[ i ].alive = 0;
        }

    //check for bullet-wall collisions
    for ( i = 0; i < MAX_SPRITES; i++ ) if (bullets[ i ].alive )
    {
        if ( map[ bullets[ i ].x ][ bullets[ i ].y ] == BRICK )
        {
            map[ bullets[ i ].x ][ bullets[ i ].y ] = EMPTY;
            bullets[ i ].alive = 0;
            // should actually destroy 1x3 instead of 1x1
            switch (bullets[i].dir)
            {
            case UP:
            case DOWN:
                if (map[bullets[i].x][bullets[i].y - 1] == BRICK) map[bullets[i].x][bullets[i].y - 1] = EMPTY;
                if (map[bullets[i].x][bullets[i].y + 1] == BRICK) map[bullets[i].x][bullets[i].y + 1] = EMPTY;
                break;
            case LEFT:
            case RIGHT:
                if (map[bullets[i].x - 1][bullets[i].y] == BRICK) map[bullets[i].x - 1][bullets[i].y] = EMPTY;
                if (map[bullets[i].x + 1][bullets[i].y] == BRICK) map[bullets[i].x + 1][bullets[i].y] = EMPTY;
                break;
            }
        }
        if ( map[ bullets[ i ].x ][ bullets[ i ].y ] == STEEL ) bullets[ i ].alive = 0;
    }

    //check for bullet-base collisions
    for ( i = 0; i < MAX_SPRITES; i++ ) if (bullets[ i ].alive )
    {
        if (map[ bullets[ i ].x ][ bullets[ i ].y ] == BASE){
            //game end
            gameOver = 1;
        }
    }

    // check for bullet-player_1 collisions
    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (bullets[i].alive == 0) continue;
        if (player1.x <= bullets[i].x && bullets[i].x <= player1.x + 2 && player1.y <= bullets[i].y && bullets[i].y <= player1.y + 2)
        {
            player1.hitPoints--;
            bullets[i].alive = 0;
            player1.x = 35;
            player1.y = 12;
        }
    }
}

void spawn_tank( int x, int y, int dir, int hitPoints )
{
    numberOfTanks++;
    totalSpawned++;
    int i;
    for ( i = 0; i < MAX_SPRITES; i++ )
        if ( !tanks[ i ].alive )
        {
            tanks[i].alive = 1;
            tanks[i].dir = dir;
            tanks[i].x = x;
            tanks[i].y = y;
            tanks[i].hitPoints = hitPoints;
            tanks[i].value = hitPoints * 100;
            break;
        }
}
