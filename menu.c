#include "global.h"

int print_menu (int sty, int x, int number_of_entries, int width, char title[], char entries[][100], int start)
{
    int i, j, k, blankspace1, blankspace2, currow = start, y = sty, key;
    char temparray[100];

    // fix the width if needed
    width = MAX(strlen(title) + 2, width);
    for (i = 0; i < number_of_entries; i++) width = MAX(strlen(&entries[i][0]) + 2, width);

    k = 0;
    move (y++, x);
    addch (ACS_ULCORNER);           /* Here the program starts to     */
                                    /* print the frame of the menu.   */
    for (i = 0; i < width; i++)     /* ULCORNER is upper left corner, */
        addch (ACS_HLINE);          /* HLINE is horizontal line.      */

    addch (ACS_URCORNER);
    printw ("\n");
    move (y++, x);

    if ((width - strlen (title)) % 2 != 0) /* If it's not possible to */
    {                                       /* perfectly center the    */
        blankspace2 = (width - strlen (title) + 1) / 2;
        blankspace1 = blankspace2 - 1;      /* menu title, it will be  */
    }                                       /* placed slightly left.   */

    else
    {
        blankspace1 = (width - strlen (title)) / 2;
        blankspace2 = blankspace1;
    }

    addch (ACS_VLINE);

    for (i = 0; i < blankspace1; i++)
        printw (" ");

    printw ("%s", title);

    for (i = 0; i < blankspace2; i++)
        printw (" ");

    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LTEE);           /* LTEE is a left tilted 'T'-like     */
                                /* shape used to connect lines to the */
    for (i = 0; i < width; i++) /* right of, above and underneath it. */
        addch (ACS_HLINE);

    addch (ACS_RTEE);
    printw ("\n");
    move (y++, x);

    for (j = 0; j < number_of_entries - 1; j++)  /* Here, the loop will print all */
    {                               /* except the last entry for the */
        addch (ACS_VLINE);          /* menu.                         */
        printw (" %s", &entries[k][0]);
        blankspace1 = width - (strlen (&entries[k][0]) + 1);
                                    /* The blankspace is after the */
        for (i = 0; i < blankspace1; i++)
            printw(" ");            /* string, since the strings   */
                                    /* will be left fixated.       */
        k++;
        addch (ACS_VLINE);
        printw ("\n");
        move (y++, x);
        addch (ACS_LTEE);

        for (i = 0; i < width; i++)
            addch (ACS_HLINE);

        addch (ACS_RTEE);
        printw ("\n");
        move (y++, x);
    }

    addch (ACS_VLINE);
    printw (" %s", &entries[k][0]);
    blankspace1 = width - (strlen (&entries[k][0]) + 1);

    for (i = 0; i < blankspace1; i++)
        printw(" ");

    k++;
    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LLCORNER);       /* The last menu entry is outside the */
                                /* loop because the lower corners are */
    for (i = 0; i < width; i++) /* different. This last entry uses    */
        addch (ACS_HLINE);      /* regular box corners to fulfill the */
                                /* menu.                              */
    addch (ACS_LRCORNER);
    printw ("\n");

    do  /* This loop is terminated when you */
    {   /* select an entry in the menu.     */
        attron (A_STANDOUT);    /* This highlights the current row. */
        blankspace1 = width - (strlen (&entries[currow - 1][0]) + 1);
        temparray[0] = ' ';     /* Also the blankspace after the */
        strcpy (&temparray[1], &entries[currow - 1][0]);
                                /* string will be highlighted.   */
        for (i = strlen (&entries[currow - 1][0]) + 1; i < width; i++)
        {
            temparray[i] = ' ';
        }

        temparray[i] = '\0';    /* The highlighted entry will be  */
        mvprintw ((sty + 3) + (currow - 1) * 2, x + 1, "%s", temparray);
        attroff (A_STANDOUT);   /* printed over the corresponding */
        key = getch();          /* non-highlighted entry.         */

        if (key == KEY_UP)
        {
            mvprintw ((sty + 3) + (currow - 1) * 2, /* First print the */
                      x + 1, "%s", temparray);      /* non-highlighted */
                                                    /* entry over the  */
            if (currow == 1)                        /* highlighted one */
                currow = number_of_entries;

            else                /* Change the currently selected entry */
                currow--;       /* according to the direction given by */
        }                       /* the keypress. Going up from the top */
                                /* moves you to the bottom.            */
        else if (key == KEY_DOWN)   /* Works just like KEY_UP above,   */
        {                           /* just in the opposite direction. */
            mvprintw ((sty + 3) + (currow - 1) * 2,
                      x + 1, "%s", temparray);

            if (currow == number_of_entries)
                currow = 1;

            else
                currow++;
        }
    }
    while (key != '\n' && key != '\r' && key != 459);

    return currow - 1;  /* The return is the row-number of the selected */
}                   /* entry. Can be 1 to "number_of_entries" (not 0). */
