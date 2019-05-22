#ifndef INPUT_LAYER_H
#define INPUT_LAYER_H

#include <ncurses.h>
#include "animate.h"
#include "canvas.h"


Canvas INPUT_CANVAS;

//functions used
void update_input(int);
void init_input();

#endif