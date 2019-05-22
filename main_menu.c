#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <menu.h>
#include "main_menu.h"
#include "main.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

//adding options for menu
char *choices[] = 
{
    "Play",
    "Help",
    "Exit",
    (char *)NULL,
};

int main menu()
{
    ITEM** my_items;
    MENU* menu;
    WINDOW* mwin; //move window

    keypad(stdscr, TRUE);

    int n_choices = ARRAY_SIZE(choices); //making an array of the choices

    my_items = (ITEM **) calloc(n_choices, sizeof(ITEM *));
   
    for(int i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], "");

    /**
     * TO DO
     */
    int width = COLS / 3;
    int height = LINES - LINES / 3;
	menu = new_menu((ITEM **) my_items);
    mwin = newwin(0, 0, 0, 0); //spawning a new window
    keypad(mwin, TRUE);

    set_menu_win(menu, mwin);
    set_menu_sub(menu, derwin(mwin, 6, 8, LINES / 2, COLS / 2));
    set_menu_mark(menu, " * ");

	refresh();

	post_menu(menu);
	wrefresh(mwin);
}

