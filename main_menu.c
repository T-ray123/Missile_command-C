#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <menu.h>
#include "main_menu.h"
#include "main.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = 
{
    "Play",
    "Help",
    "Exit",
    (char *)NULL,
};