#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "ui_layer.h"
#include "defense_layer.h"
#include "main.h"
#include "animate.h"



static long int score = 0;
static int round = 1;
static int building_count = 10;
static struct Base* bases[] = {&BASE_LEFT, &BASE_MID, &BASE_RIGHT};


static void draw_building(Coord*, int);
static void clear_building(Coord*, int);
static void update_score();
static void update_buildings();
static void update_base();
static void reset_buildings();


void init_display() {
    DISPLAY = newwin(0, 0, 0, 0);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    wattron(DISPLAY, COLOR_PAIR(5));
}