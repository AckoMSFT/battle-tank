#include "global.h"

// moves the tank
void move_tank ( Tank *tank, int direction){

    //if this tank moved TANKSPEED earlier, just ignore. else, set movestate to 0
    if (tank->moveState < TANKSPEED) return;

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
    if (DEBUG){
        move(26,50);
        printw("whats with this? %d %d %d",x, y, left);

    }
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
    if (tank->shootState < SHOOTSPEED) return;

    if (DEBUG) {
            move(3,50);
            printw("shooting from shoot state %d", tank->shootState);
    }

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
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( bullets[ i ].valid == false )
        {
            bullets[ i ].valid = true;
            bullets[ i ].x = x;
            bullets[ i ].y = y;
            bullets[ i ].dir = tank->dir;
            bullets[ i ].state = 0;
            bullets[i].origin = origin;

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
    for(i=0; i < MAXSPRITES ; i++){
        if (tanks[ i ].valid == true){

            if (tanks[ i ].moveState < TANKSPEED){
                tanks[ i ].moveState++;
            }

            if (tanks[ i ].shootState < SHOOTSPEED){
                tanks[ i ].shootState++;
            }

        }


    }
    //also for mytank
    if (myTank.shootState < SHOOTSPEED) myTank.shootState++;
    if (myTank.moveState < TANKSPEED) myTank.moveState++;


    for ( i = 0; i < MAXSPRITES; i++ )
        if ( bullets[ i ].valid == true )
        {
            bullets[ i ].state++;
            if ( bullets[ i ].state == BULLETSPEED )
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

void collision() // Check for collisions of tanks and bullets, respectively bullets and bullets
{
    int i, j, di, dj;
    //check for tank-bullet colisions
    for (i = 0; i < MAXSPRITES; i++)
        for (j = 0; j < MAXSPRITES; j++) if (tanks[i].valid && bullets[j].valid )
        {
            if ( bullets[j].origin == 1 ) continue;
            bool hit = false;
            for( di = 0; di < 3; di++) for( dj = 0; dj < 3; dj++){

                if ( ( tanks[ i ].x + di == bullets[ j ].x ) && ( tanks[ i ].y + dj == bullets[ j ].y ) ) hit = true;
            }
            if ( hit )
            {
                tanks[i].lives--;
                bullets[ j ].valid = false;
                if (tanks[i].lives <= 0)
                {
                    tanks[i].valid = false;
                    myScore += tanks[i].value;
                }
            }
    }

    //check for bullet-bullet colisions
    for ( i = 0; i < MAXSPRITES; i++ )
        for ( j = 0; j < MAXSPRITES; j++ ) if (bullets[ i ].valid && bullets[ j ].valid)
        if ( ( i != j ) && ( bullets[ i ].x == bullets[ j ].x ) && ( bullets[ i ].y == bullets[ j ].y ) )
        {
            bullets[ i ].valid = 0;
            bullets[ j ].valid = 0;
        }

    //check for bullet-frame collisions
    for ( i = 0; i < MAXSPRITES; i++ ) if (bullets[ i ].valid)
        if ( bullets[ i ].x < 0 || bullets[ i ].y < 0 || bullets[ i ].x >= MAP_SIZE || bullets[ i ].y >= MAP_SIZE  )
        {
            bullets[ i ].valid = 0;
        }

    //check for bullet-wall collisions
    for ( i = 0; i < MAXSPRITES; i++ ) if (bullets[ i ].valid )
    {
        if ( map[ bullets[ i ].x ][ bullets[ i ].y ] == BRICK )
        {
            map[ bullets[ i ].x ][ bullets[ i ].y ] = EMPTY;
            bullets[ i ].valid = 0;
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
        if ( map[ bullets[ i ].x ][ bullets[ i ].y ] == STEEL ) bullets[ i ].valid = 0;
    }

    //check for bullet-base collisions
    for ( i = 0; i < MAXSPRITES; i++ ) if (bullets[ i ].valid )
    {
        if (map[ bullets[ i ].x ][ bullets[ i ].y ] == BASE){
            //game end
            gameOver = 1;
        }
    }

    // check for bullet-myTank collisions
    for (i = 0; i < MAXSPRITES; i++)
    {
        if (bullets[i].valid == 0) continue;
        if (myTank.x <= bullets[i].x && bullets[i].x <= myTank.x + 2 && myTank.y <= bullets[i].y && bullets[i].y <= myTank.y + 2)
        {
            myTank.lives--;
            bullets[i].valid = 0;
        }
    }
}

void spawn_tank( int x, int y, int dir, int lives )
{
    numberOfTanks++;
    int i;
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( !tanks[ i ].valid )
        {
            tanks[ i ].valid = 1;
            tanks[ i ].dir = dir;
            tanks[ i ].x = x;
            tanks[ i ].y = y;
            tanks[i].lives = lives;
            tanks[i].value = lives * 100;
            break;
        }
}
