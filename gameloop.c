#include <time.h>
#include <stdio.h>
#include <curses.h>
#include "global.h"
#include "kletve.h"
#include "editor.h"
#include "engine.h"
#include "gameloop.h"

void choose_level(){
    //this is for choosing level and difficulty, not done yet.

    load_map("Level0x01.map");
    gameDifficulty = 0;
    print_map();
    start_game();
}

void start_game(){

    time_t current_time;
    char* c_time_string;
    /* Obtain current time as seconds elapsed since the Epoch. */
    current_time = time(NULL);
    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    int i,keyPressed,enemySpawn,x,y;
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

        if (DEBUG) {
            move(2,50);
            printw("%s",c_time_string);
        }
        if (kbhit()){

            //get the last pressed key
            while(kbhit()){
                    keyPressed = getch();
            }

            if (DEBUG) {
                    move(3,50);
                    printw("not pressed");
            }
            switch(keyPressed){

                case KEY_RIGHT:
                case KEY_LEFT:
                case KEY_UP:
                case KEY_DOWN:
                    move_tank(&myTank, keyPressed - KEY_DOWN);
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

        //check if we should spawn an enemy tank
        enemySpawn++;
        if (enemySpawn == confDiff[ gameDifficulty ].spawn){
            enemySpawn = 0;
            //find me a spot for new enemy tank
            find_space_tank(&x,&y);

            //if valid
            if (x!=-1){
                spawn_tank(x,y,DOWN);

            }

        }

        update_states();
        collision();

        print_map();
        Sleep(sleepTime);

    }

}
