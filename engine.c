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
void shoot( Tank *tank ) // Spawns new bullet after shoot command
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
        if ( !bullets[ i ].val )
        {
            bullets[ i ].val = 1;
            bullets[ i ].x = x;
            bullets[ i ].y = y;
            bullets[ i ].dir = tank->dir;
            bullets[ i ].state = 0;

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
        if (tanks[ i ].val){

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
        if ( bullets[ i ].val )
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
    for ( i = 0; i < MAXSPRITES; i++ )
        for ( j = 0; j < MAXSPRITES; j++ ){
            //dont check if not valid
            if (!tanks[ i ].val || !bullets[ j ].val) continue;

            for( di = 0; di < 3; di++) for( dj = 0; dj < 3; dj++){

                if ( ( tanks[ i ].x + di == bullets[ j ].x ) && ( tanks[ i ].y + dj == bullets[ j ].y ) )
                {
                    bullets[ i ].val = 0;
                    tanks[ i ].val = 0;
                }
            }
    }

    //check for bullet-bullet colisions
    for ( i = 0; i < MAXSPRITES; i++ )
        for ( j = 0; j < MAXSPRITES; j++ )
        if ( ( i != j ) && ( bullets[ i ].x == bullets[ j ].x ) && ( bullets[ i ].y == bullets[ j ].y ) )
        {
            bullets[ i ].val = 0;
            bullets[ j ].val = 0;
        }

    //check for bullet-frame collisions
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( bullets[ i ].x < 0 || bullets[ i ].y < 0 || bullets[ i ].x >= MAP_SIZE || bullets[ i ].y >= MAP_SIZE  )
        {
            bullets[ i ].val = 0;
        }

    for ( i = 0; i < MAXSPRITES; i++ )
    {
        if ( map[ bullets[ i ].x ][ bullets[ i ].y ] == BRICK )
        {
            map[ bullets[ i ].x ][ bullets[ i ].y ] = EMPTY;
            bullets[ i ].val = 0;
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
        if ( map[ bullets[ i ].x ][ bullets[ i ].y ] == STEEL ) bullets[ i ].val = 0;
    }
}

void spawn_tank( int x, int y, int dir )
{
    int i;

    if (DEBUG){
        move(22,50);
        printw("printing enemy tank ! %d",i);

    }
    for ( i = 0; i < MAXSPRITES; i++ )
        if ( !tanks[ i ].val )
        {
            tanks[ i ].val = 1;
            tanks[ i ].dir = dir;
            tanks[ i ].x = x;
            tanks[ i ].y = y;
            break;
        }
}
