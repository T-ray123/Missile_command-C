#ifndef DEFENSE_LAYER_H
#define DEFENSE_LAYER_H

#include "canvas.h"


Canvas DEFENSE_CANVAS;

struct Base
 {
    int missile_count;
    Coord position;
} BASE_LEFT, BASE_MID, BASE_RIGHT;


void init_defense();
void update_defense(int);
void reset_defense();


#endif