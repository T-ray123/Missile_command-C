#ifndef UI_LAYER_H
#define UI_LAYER_H

#include <ncurses.h>

WINDOW *DISPLAY;

void init_display();
void update_display();
void add_score(int);
void destroy_building();
void increment_round();
void reset_ui();
int get_round();

#endif