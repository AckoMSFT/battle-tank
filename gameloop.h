#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED
#define DEBUG 0

void choose_level(){
    //this is for choosing level, not done yet.

    load_map("Level0x01.map");
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

    int i,keyPressed;

    //init some elements
    gameOver = 0;
    for (i=0; i<MAXSPRITES ; i++){
        tanks[i].val = bullets[i].val = 0;

    }


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

            keyPressed = getch();

            if (DEBUG) {
                    move(3,50);
                    printw("not pressed");
            }
            switch(keyPressed){

                case KEY_RIGHT:
                    go_right(&myTank);
                    if (DEBUG) {
                            move(3,50);
                        printw("pressed RIGHT");
                        refresh();
                    }
                    break;
                case KEY_LEFT:
                    go_left(&myTank);
                    if (DEBUG) printw("pressed LEFT");
                    break;
                case KEY_UP:
                    go_up(&myTank);
                    if (DEBUG) printw("pressed UP");
                    break;
                case KEY_DOWN:
                    go_down(&myTank);
                    if (DEBUG) printw("pressed DOWN");
                    break;
                default:
                    if (DEBUG) printw("pressed %c, but keyright is %c, and keyright == pressed %d",keyPressed,KEY_RIGHT,keyPressed==KEY_RIGHT);
            }

            if (DEBUG ) refresh();
        }

        print_map();
        Sleep(1000/FRAMES_PER_SEC);


    }

}




#endif // GAMELOOP_H_INCLUDED
