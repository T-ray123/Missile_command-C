#ifndef ALIEN_LAYER_H
#define ALIEN_LAYER_H

#include "canvas.h"


Canvas ALIEN_CANVAS;


void reset_alien();
void init_alien();
void update_alien(int);
bool is_alien_done();

#endif