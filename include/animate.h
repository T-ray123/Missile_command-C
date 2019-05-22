#ifndef ANIMATE_H //checks whether the token has been defined earlier
#define ANIMATE_H

#include <ncurses.h>
#include "canvas.h"

#define SECOND 1000000L

/**
 * function pointers pointing to the different functions used in the program
 */
void lerp(Vector*);
void set_animation(Sprite*, Coord*, Coord*, int);
void update_animation(Canvas*, Sprite*);
double distance(Coord*, Coord*);
double slope(Coord*, Coord*);
bool cmpcoord(Coord*, Coord*);
bool is_animation_done(Sprite*);
unsigned long get_time();



#endif