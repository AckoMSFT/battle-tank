#include "global.h"

int print_menu (int starty, int x, int number_of_entries, int width, char title[], char entries[][100], int idx)
{
    attron ( A_BOLD );
    int i, j, k, left_space, right_space, y = starty, key;
    char temp[100];
    width = MAX(strlen(title) + 2, width);
    for (i = 0; i < number_of_entries; i++) width = MAX(strlen(&entries[i][0]) + 2, width);
    k = 0;
    move (y++, x);
    addch (ACS_ULCORNER);
    for (i = 0; i < width; i++) addch (ACS_HLINE);
    addch (ACS_URCORNER);
    printw ("\n");
    move (y++, x);
    if ((width - strlen (title)) % 2 != 0)
    {
        right_space = (width - strlen (title) + 1) / 2;
        left_space = right_space - 1;
    }
    else
    {
        left_space = (width - strlen (title)) / 2;
        right_space = left_space;
    }
    addch (ACS_VLINE);
    for (i = 0; i < left_space; i++) printw (" ");
    printw ("%s", title);
    for (i = 0; i < right_space; i++) printw (" ");
    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LTEE);
    for (i = 0; i < width; i++) addch (ACS_HLINE);
    addch (ACS_RTEE);
    printw ("\n");
    move (y++, x);
    for (j = 0; j < number_of_entries - 1; j++)
    {
        addch (ACS_VLINE);
        printw (" %s", &entries[k][0]);
        right_space = width - (strlen (&entries[k][0]) + 1);
        for (i = 0; i < right_space; i++) printw(" ");
        k++;
        addch (ACS_VLINE);
        printw ("\n");
        move (y++, x);
        addch (ACS_LTEE);
        for (i = 0; i < width; i++) addch (ACS_HLINE);
        addch (ACS_RTEE);
        printw ("\n");
        move (y++, x);
    }
    addch (ACS_VLINE);
    printw (" %s", &entries[k][0]);
    right_space = width - (strlen (&entries[k][0]) + 1);
    for (i = 0; i < right_space; i++) printw(" ");
    k++;
    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LLCORNER);
    for (i = 0; i < width; i++) addch (ACS_HLINE);
    addch (ACS_LRCORNER);
    printw ("\n");
    do
    {
        attroff ( A_BOLD );
        attron ( A_STANDOUT );
        left_space = width - (strlen (&entries[idx - 1][0]) + 1);
        temp[0] = ' ';
        strcpy (&temp[1], &entries[idx - 1][0]);
        for (i = strlen (&entries[idx - 1][0]) + 1; i < width; i++) temp[i] = ' ';
        temp[i] = '\0';
        mvprintw ((starty + 3) + (idx - 1) * 2, x + 1, "%s", temp);
        attroff ( A_STANDOUT );
        key = getch();
        if (key == KEY_UP)
        {
            mvprintw ((starty + 3) + (idx - 1) * 2, x + 1, "%s", temp);
            if (idx == 1) idx = number_of_entries;
            else idx--;
        }
        else if (key == KEY_DOWN)
        {
            mvprintw ((starty + 3) + (idx - 1) * 2, x + 1, "%s", temp);
            if (idx == number_of_entries) idx = 1;
            else idx++;
        }
        attron ( A_BOLD );
    }
    while (key != '\r' && key != '\n' );
    attroff ( A_BOLD );
    return idx - 1;
}
