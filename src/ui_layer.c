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

/**
 * adding function for initialising the display
 */
void init_display() 

{
    DISPLAY = newwin(0, 0, 0, 0);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    wattron(DISPLAY, COLOR_PAIR(5)); //The routine attron turns on the named attributes without affecting any others.
}

//10 because each base has 10 missiles in total 
void update_display() 
{
    update_buildings();
    update_score();
    update_base();
    mvwprintw(DISPLAY, 1, COLS - 10, "Round %d ", round);
}
static void update_score() {
    mvwprintw(DISPLAY, 1, COLS / 2, "Score: %d ", score);
}

//structuring the base
static void update_base()
 {
    for (int i = 0; i < 3; i++) 
    {
        struct Base* base = bases[i];

        draw_building(&base->position, 5);
        mvwprintw(
            DISPLAY,
            base->position.y - 4,  //the difference in terms of pixels toward each building
            base->position.x - 6,
            "%d ", base->missile_count
        );
    }
}

/*
 * Only drawing the buildings on the map
*/
static void update_buildings() 
{
    int xincrement = COLS * .8 / 10;
    Coord pos = { .x = xincrement * 2, .y = LINES };
    for (int i = 0; i < 10; i++) 
    {
        if (i < building_count) 
        {
            draw_building(&pos, 1); //by one pixel
        } 
        else 
        {
            clear_building(&pos, 1);
        }
        pos.x += xincrement;
    }
}

static void draw_building(Coord* position, int size)
 {
    int topy = position->y - size;
    int leftx = position->x - size * 1.5;
    int rightx = position->x + size * 1.5;

    mvwaddch(DISPLAY, topy, leftx, ACS_ULCORNER);
    mvwhline(DISPLAY, topy, leftx + 1, ACS_HLINE, size * 3 - 1);
    mvwaddch(DISPLAY, topy, rightx, ACS_URCORNER);
    mvwvline(DISPLAY, topy + 1, rightx, ACS_VLINE, LINES - topy - 1);
    mvwvline(DISPLAY, topy + 1, leftx, ACS_VLINE, LINES - topy - 1);
}


static void clear_building(Coord* position, int size) 
{
    int topy = position->y - size;
    int leftx = position->x - size * 1.5;
    int rightx = position->x + size * 1.5;

    mvwaddch(DISPLAY, topy, leftx, ' ');
    mvwhline(DISPLAY, topy, leftx + 1, ' ', size * 3 - 1);
    mvwaddch(DISPLAY, topy, rightx, ' ');
    mvwvline(DISPLAY, topy + 1, rightx, ' ', LINES - topy - 1);
    mvwvline(DISPLAY, topy + 1, leftx, ' ', LINES - topy - 1);
}
 /**
  * adding score
  */
void add_score(int val)

 {
    score += val;
}


void destroy_building() 

{
    --building_count;  
    // No more buildings to destroy
    if (!building_count) 
    {
        round = 1;
        score = 0;

        mvprintw(LINES / 2, COLS / 2, "You lose. <press any key>"); //if you run out of missiles
        lose_game();
        // Pause for the user.
        getch();
    }
}


void reset_ui() 
{
    reset_buildings();
}


/*
 * Play a short incrementing animation for the user.
*/
void increment_round() 
{
    long timebuff = get_time(); //used long because the timebuffer is supposed to be of big range

    for (int i = 0; i < 3; i++)
     {
        while (bases[i]->missile_count) 
        {
            if (get_time() - timebuff > SECOND / 4) 
            {
                --bases[i]->missile_count;
                score += 125;
                timebuff = get_time();
            }
            mvprintw(LINES / 2, COLS / 2, "Success!");
            update();
        }
    }

    timebuff = get_time();
    for (int i = 0; i < building_count; i++)
     {
        score += 300;
        --building_count;
        while (get_time() - timebuff < SECOND / 3) 
        {
            update();
        }
        timebuff = get_time();
    }
    reset_buildings();
    ++round;
}